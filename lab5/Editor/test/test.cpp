#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Command/CChangeTitleCommand/CChangeTitleCommand.h"
#include "../src/Command/CInsertDocumentItemCommand/CInsertDocumentItemCommand.h"
#include "../src/Command/CDeleteItemCommand/CDeleteItemCommand.h"
#include "../src/Command/Exception/CWrongIndexOfItemInDocumentException/CWrongIndexOfItemInDocumentException.h"
#include "../src/Content/CImage/CImage.h"
#include "../src/Content/CParagraph/CParagraph.h"
#include "../src/Document/CDocument/CDocument.h"
#include "../src/Client/CMenu/CMenu.h"
#include "../test/Command/CTestCommand/CTestCommand.h"

TEST_CASE("check creation image")
{
	CHistory history;

	SECTION("construction with exceptions(wrong extention)")
	{
		REQUIRE_THROWS_AS(CImage("hello.js", 200, 200, history), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(file does not exist)")
	{
		REQUIRE_THROWS_AS(CImage("hello.png", 200, 200, history), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(wrong size)")
	{
		REQUIRE_THROWS_AS(CImage("../test/image.png", 0, 200, history), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, -1, history), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, 20000, history), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 20000, 200, history), WrongImageSizeException);
	}

	SECTION("create image without exceptions")
	{
		CImage image("../test/image.png", 200, 350, history);

		THEN("Getters have to get right values")
		{
			REQUIRE(image.GetWidth() == 200);
			REQUIRE(image.GetHeight() == 350);
			REQUIRE_NOTHROW(image.GetPath());
		}
	}
}

TEST_CASE("check creation paragraphs")
{
	CHistory history;

	SECTION("create image without exceptions")
	{
		CParagraph paragraph("hello", history);

		REQUIRE(paragraph.GetText() == "hello");
	}
}

TEST_CASE("test DocumentItem and ConstDocumentItem")
{
	CHistory history;

	SECTION("create DocumentItem via IImage")
	{
		CImage image("../test/image.png", 200, 200, history);
		CDocumentItem documentItem(std::make_shared<CImage>(image));

		WHEN("take from document item paragraph")
		{
			THEN("result ptr will be nullptr")
			{
				REQUIRE(documentItem.GetParagraph() == nullptr);
			}
		}

		WHEN("take from document item image")
		{
			THEN("params of result will be the same with original image")
			{
				REQUIRE(documentItem.GetImage()->GetPath() == image.GetPath());
				REQUIRE(documentItem.GetImage()->GetWidth() == image.GetWidth());
				REQUIRE(documentItem.GetImage()->GetHeight() == image.GetHeight());
			}
		}
	}

	SECTION("create DocumentItem via IParagraph")
	{
		CParagraph paragraph("hello", history);
		CDocumentItem documentItem(std::make_shared<CParagraph>(paragraph));

		WHEN("take from document item paragraph")
		{
			THEN("text of paragraph will be the same with the original paragraph")
			{
				REQUIRE(documentItem.GetParagraph()->GetText() == paragraph.GetText());
			}
		}

		WHEN("take from document item image")
		{
			THEN("result ptr will be nullptr")
			{
				REQUIRE(documentItem.GetImage() == nullptr);
			}
		}
	}

	SECTION("create ConstDocumentItem via IImage")
	{
		CImage image("../test/image.png", 200, 200, history);
		CConstDocumentItem constDocumentItem(std::make_shared<CImage>(image));

		WHEN("take from document item paragraph")
		{
			THEN("result ptr will be nullptr")
			{
				REQUIRE(constDocumentItem.GetParagraph() == nullptr);
			}
		}

		WHEN("take from document item image")
		{
			THEN("params of result will be the same with original image")
			{
				REQUIRE(constDocumentItem.GetImage()->GetPath() == image.GetPath());
				REQUIRE(constDocumentItem.GetImage()->GetWidth() == image.GetWidth());
				REQUIRE(constDocumentItem.GetImage()->GetHeight() == image.GetHeight());
			}
		}
	}

	SECTION("create ConstDocumentItem via IParagraph")
	{
		CParagraph paragraph("hello", history);
		CConstDocumentItem constDocumentItem(std::make_shared<CParagraph>(paragraph));

		WHEN("take from document item paragraph")
		{
			THEN("text of paragraph will be the same with the original paragraph")
			{
				REQUIRE(constDocumentItem.GetParagraph()->GetText() == paragraph.GetText());
			}
		}

		WHEN("take from document item image")
		{
			THEN("result ptr will be nullptr")
			{
				REQUIRE(constDocumentItem.GetImage() == nullptr);
			}
		}
	}
}

TEST_CASE("test history functional")
{
	CHistory history;

	SECTION("history is empty")
	{
		REQUIRE(history.CanUndo() == false);
		REQUIRE(history.CanRedo() == false);
	}

	SECTION("1 command in history")
	{
		history.AddAndExecuteCommand(std::make_unique<CTestCommand>());

		THEN("can undo, but cannot redo")
		{
			REQUIRE(history.CanUndo() == true);
			REQUIRE(history.CanRedo() == false);
		}

		WHEN("undo command")
		{
			history.Undo();

			THEN("can redo but cannot undo")
			{
				REQUIRE(history.CanUndo() == false);
				REQUIRE(history.CanRedo() == true);
			}

			THEN("after redo will be able undo, but not redo")
			{
				history.Redo();

				REQUIRE(history.CanUndo() == true);
				REQUIRE(history.CanRedo() == false);
			}
		}
	}

	SECTION("deleting redo commands after adding new command in undo")
	{
		history.AddAndExecuteCommand(std::make_unique<CTestCommand>());
		history.AddAndExecuteCommand(std::make_unique<CTestCommand>());
		history.AddAndExecuteCommand(std::make_unique<CTestCommand>());

		WHEN("undo 2 command command and add 1 command")
		{
			history.Undo();
			history.Undo();
			history.AddAndExecuteCommand(std::make_unique<CTestCommand>());

			THEN("can redo but cannot undo")
			{
				REQUIRE(history.CanRedo() == false);
			}
		}
	}

	SECTION("adding limit number command")
	{
		WHEN("add 20 command to history")
		{
			for (auto index = 0; index < 20; index ++)
			{
				history.AddAndExecuteCommand(std::make_unique<CTestCommand>());
			}

			THEN("only last 10 will be available")
			{
				auto undoCount = 0;
				for (auto index = 0; index < 20; index ++)
				{
					if (history.CanUndo())
					{
						undoCount++;
					}

					history.Undo();
				}

				REQUIRE(history.CanUndo() == false);
				REQUIRE(undoCount == 10);
			}
		}
	}
}

TEST_CASE("test of change title command")
{
	std::string oldTitle = "Garbage";
	std::string newTitle = "For sale";

	CChangeTitleCommand changeTitleCommand(oldTitle, newTitle);

	WHEN("change title")
	{
		changeTitleCommand.Execute();

		THEN("new title will be `For sale`")
		{
			REQUIRE(oldTitle == "For sale");
		}

		THEN("after unexecute new title will be `Garbage`")
		{
			changeTitleCommand.Unexecute();

			REQUIRE(oldTitle == "Garbage");
		}
	}
}

TEST_CASE("test of change text paragraph command")
{
	std::string oldText = "Garbage";
	std::string newText = "For sale";

	CReplaceTextParagraphCommand replaceTextParagraphCommand(oldText, newText);

	WHEN("change text")
	{
		replaceTextParagraphCommand.Execute();

		THEN("new text will be `For sale`")
		{
			REQUIRE(oldText == "For sale");
		}

		THEN("after unexecute new text will be `Garbage`")
		{
			replaceTextParagraphCommand.Unexecute();

			REQUIRE(oldText == "Garbage");
		}
	}
}

TEST_CASE("test of resize image command")
{
	SECTION("check non throwing action")
	{
		int currentWidth = 150;
		int currentHeight = 150;
		int newWidth = 250;
		int newHeight = 250;

		CResizeImageCommand resizeImageCommand(currentWidth, currentHeight, newWidth, newHeight);

		WHEN("change size")
		{
			resizeImageCommand.Execute();

			THEN("new size will be 250 250")
			{
				REQUIRE(currentWidth == 250);
				REQUIRE(currentHeight == 250);
			}

			THEN("after unexecute new size will be 150 150")
			{
				resizeImageCommand.Unexecute();

				REQUIRE(currentWidth == 150);
				REQUIRE(currentHeight == 150);
			}
		}
	}

	SECTION("check throwing action")
	{
		int currentWidth = 150;
		int currentHeight = 150;
		int newWidth = 0;
		int newHeight = 250;

		WHEN("change size")
		{
			THEN("exception")
			{
				REQUIRE_THROWS_AS(CResizeImageCommand(currentWidth, currentHeight, newWidth, newHeight), WrongImageSizeException);
			}
		}
	}
}

TEST_CASE("test of insert document item command")
{
	CHistory history;
	CDocumentItem firstParagraph(std::make_unique<CParagraph>("hello", history));
	CDocumentItem secondParagraph(std::make_unique<CParagraph>("bonjour", history));
	CDocumentItem image(std::make_unique<CImage>("../test/image.png", 200, 350, history));

	std::vector<CDocumentItem> items{};

	SECTION("check throwing exception")
	{
		WHEN("add on 1 position")
		{
			THEN("exception about wrong index")
			{
				REQUIRE_THROWS_AS(CInsertDocumentItemCommand(items, firstParagraph, 1), CWrongIndexOfItemInDocumentException);
			}
		}
	}

	SECTION("check adding to end")
	{
		WHEN("add on 1 position, but before add at 0")
		{
			CInsertDocumentItemCommand(items, firstParagraph, 0).Execute();

			THEN("first item will be paragraph with `hello`")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetParagraph()->GetText() == "hello");
			}

			THEN("add to end")
			{
				REQUIRE_NOTHROW(CInsertDocumentItemCommand(items, firstParagraph, items.size()));
			}
		}
	}

	SECTION("check adding and removing elements")
	{
		WHEN("add 1 paragraph")
		{
			CInsertDocumentItemCommand insertDocumentItemCommand(items, firstParagraph, 0);
			insertDocumentItemCommand.Execute();

			THEN("first item will be paragraph with `hello`")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetParagraph()->GetText() == "hello");
			}

			insertDocumentItemCommand.Unexecute();
			THEN("after removing paragraph, document will be empty")
			{
				REQUIRE(items.empty());
			}
		}

		WHEN("add 1 image")
		{
			CInsertDocumentItemCommand insertDocumentItemCommand(items, image, 0);
			insertDocumentItemCommand.Execute();

			THEN("first item will be image with width 200")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetImage()->GetWidth() == 200);
			}

			insertDocumentItemCommand.Unexecute();
			THEN("after removing image, document will be empty")
			{
				REQUIRE(items.size() == 0);
			}
		}
	}
}

TEST_CASE("check delete item command")
{
	CHistory history;
	CDocumentItem firstParagraph(std::make_unique<CParagraph>("hello", history));
	CDocumentItem secondParagraph(std::make_unique<CParagraph>("bonjour", history));
	CDocumentItem image(std::make_unique<CImage>("../test/image.png", 200, 350, history));
	std::vector<CDocumentItem> items{};

	SECTION("check throwing")
	{
		WHEN("delete from empty document")
		{
			THEN("throw exception")
			{
				REQUIRE_THROWS_AS(CDeleteItemCommand(items, 0), CWrongIndexOfItemInDocumentException);
			}
		}

		WHEN("delete from non empty document with wrong index")
		{
			items.push_back(firstParagraph);

			THEN("throw exception")
			{
				REQUIRE_THROWS_AS(CDeleteItemCommand(items, 1), CWrongIndexOfItemInDocumentException);
			}
		}
	}

	SECTION("check deleting from")
	{
		items.push_back(firstParagraph);
		items.push_back(secondParagraph);

		WHEN("delete second item")
		{
			CDeleteItemCommand deleteSecondItemCommand(items, 1);
			CDeleteItemCommand deleteFirstItemCommand(items, 0);

			deleteSecondItemCommand.Execute();
			THEN("size of document will be 1")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetParagraph()->GetText() == "hello");
			}
			deleteSecondItemCommand.Unexecute();

			THEN("after unexecute size will be 2")
			{
				REQUIRE(items.size() == 2);
			}

			deleteFirstItemCommand.Execute();
			THEN("size of document will be 1")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetParagraph()->GetText() == "bonjour");
			}
			deleteFirstItemCommand.Unexecute();

			THEN("after unexecute size will be 2")
			{
				REQUIRE(items.size() == 2);
			}
		}
	}

	SECTION("check deleting image")
	{
		items.push_back(image);
		CDeleteItemCommand deleteFirstItemCommand(items, 0);

		deleteFirstItemCommand.Execute();
		THEN("after removing image, document will be empty")
		{
			REQUIRE(items.size() == 0);
		}

		deleteFirstItemCommand.Unexecute();
		THEN("first item will be image with width 200")
		{
			REQUIRE(items.size() == 1);
			REQUIRE(items[0].GetImage()->GetWidth() == 200);
		}
	}
}

TEST_CASE("check menu functionality")
{
	SECTION("check adding only one commands")
	{
		std::istringstream iss("hello");
		std::ostringstream oss;
		std::ostringstream result;
		CMenu menu(iss, oss);

		WHEN("add command print hello and run")
		{
			menu.AddCommand("hello", "print greetings to your pen friend", [&](std::istream& in) { result << "bonjour"; });
			menu.Run();

			THEN("in result will be 'bonjour'")
			{
				REQUIRE(result.str() == "bonjour");
			}
		}
	}

	SECTION("check adding two commands")
	{
		std::istringstream iss("hello\nbonjour");
		std::ostringstream oss;
		std::ostringstream result;
		CMenu menu(iss, oss);

		WHEN("add command print two different greetings and run")
		{
			menu.AddCommand("hello", "print greetings to your pen friend", [&](std::istream& in) { result << "bonjour"; });
			menu.AddCommand("bonjour", "print greetings to your pen friend", [&](std::istream& in) { result << "hello"; });
			menu.Run();

			THEN("in result will be 'bonjourhello'")
			{
				REQUIRE(result.str() == "bonjourhello");
			}
		}

		WHEN("add command print two different greetings and run")
		{
			menu.AddCommand("hello", "print greetings to your pen friend", [&](std::istream& in) { result << "bonjour"; });
			menu.AddCommand("bonjour", "print greetings to your pen friend", [&](std::istream& in) { result << "hello"; });
			menu.ShowCommands();

			THEN("in oss will command descriptions")
			{
				REQUIRE(oss.str() == "1. <hello>: print greetings to your pen friend\n2. <bonjour>: print greetings to your pen friend\n");
			}
		}
	}

	SECTION("check call undefined command")
	{
		std::istringstream iss("hola!");
		std::ostringstream oss;
		std::ostringstream result;
		CMenu menu(iss, oss);

		WHEN("add command print two different greetings and run")
		{
			menu.AddCommand("hello", "print greetings to your pen friend", [&](std::istream& in) { result << "bonjour"; });
			menu.AddCommand("bonjour", "print greetings to your pen friend", [&](std::istream& in) { result << "hello"; });
			menu.Run();

			THEN("result will be empty")
			{
				REQUIRE(result.str().empty());
			}

			THEN("oss will be contain error message")
			{
				REQUIRE(oss.str() == ">Error, wrong command\n>");
			}
		}
	}

	SECTION("check exiting")
	{
		std::istringstream iss("hello\nexit\nbonjour");
		std::ostringstream oss;
		std::ostringstream result;
		CMenu menu(iss, oss);

		WHEN("add command print two different greetings and run")
		{
			menu.AddCommand("hello", "print greetings to your pen friend", [&](std::istream& in) { oss << "bonjour\n"; });
			menu.AddCommand("bonjour", "print greetings to your pen friend", [&](std::istream& in) { oss << "hello\n"; });
			menu.AddCommand("exit", "exit from program", [&](std::istream& in) { menu.Exit(); });
			menu.Run();

			THEN("in oss will be only 'bonjour'")
			{
				REQUIRE(oss.str() == ">bonjour\n>");
			}
		}
	}
}

TEST_CASE("check document functionality")
{
	CDocument document;

	SECTION("empty document")
	{
		THEN("empty document has 0 size and empty title")
		{
			REQUIRE(document.GetTitle().empty());
			REQUIRE(document.GetItemsCount() == 0);
		}
	}

	SECTION("default one element in document")
	{
		WHEN("insert paragraph with text 'hello'")
		{
			document.InsertParagraph("hello", 0);

			THEN("size == 1, item is paragraph")
			{
				REQUIRE(document.GetTitle().empty());
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE_NOTHROW(document.GetItem(0));
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "hello");
			}
		}
	}

	SECTION("check setting title")
	{
		WHEN("set title 'first'")
		{
			document.SetTitle("first");

			THEN("size == 0, title is 'first'")
			{
				REQUIRE(document.GetTitle() == "first");
				REQUIRE(document.GetItemsCount() == 0);
				REQUIRE(document.CanUndo());
			}

			document.Undo();
			THEN("after undo, title become empty")
			{
				REQUIRE(document.GetTitle().empty());
			}
		}
	}

	SECTION("check resizing image")
	{
		WHEN("add paragraph and resize it")
		{
			document.InsertParagraph("hello", 0);

			THEN("exception")
			{
				REQUIRE_THROWS_AS(document.ResizeImage(0, 200, 200), CWrongItemException);
			}
		}

		WHEN("add image")
		{
			document.InsertImage("../test/image.png", 200, 200, 0);

			THEN("all data of image is consistent")
			{
				REQUIRE(document.GetTitle().empty());
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.CanUndo());
				REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
				REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 200);
			}

			document.ResizeImage(0, 100, 100);

			THEN("all data of image is consistent")
			{
				REQUIRE(document.GetTitle().empty());
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.CanUndo());
				REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 100);
				REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 100);
			}

			document.Undo();
			THEN("after undo, size become 200 x 200")
			{
				REQUIRE(document.GetTitle().empty());
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.CanUndo());
				REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
				REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 200);
			}
		}
	}

	SECTION("check deleting items")
	{
		WHEN("add image and paragraph")
		{
			document.InsertImage("../test/image.png", 200, 200, 0);
			document.InsertParagraph("hello", 0);

			THEN("two elements in document")
			{
				REQUIRE(document.GetTitle().empty());
				REQUIRE(document.GetItemsCount() == 2);
				REQUIRE(document.CanUndo());
			}

			document.RemoveItem(0);
			THEN("after deleting first, new first will be image")
			{
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.GetItem(0).GetImage());
			}
		}
	}

	SECTION("check replacing text in paragraph")
	{
		WHEN("add image and replace text")
		{
			document.InsertImage("../test/image.png", 200, 200, 0);

			THEN("exception")
			{
				REQUIRE_THROWS_AS(document.ReplaceParagraphText(0, "hello"), CWrongItemException);
			}
		}

		WHEN("add paragraph and replace text")
		{
			document.InsertParagraph("hello", 0);

			document.ReplaceParagraphText(0, "bonjour");

			THEN("new text")
			{
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "bonjour");
			}

			document.Undo();
			THEN("after undo text become 'hello'")
			{
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "hello");
			}

			document.Redo();
			THEN("after redo text become 'bonjour'")
			{
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "bonjour");
			}
		}
	}
}