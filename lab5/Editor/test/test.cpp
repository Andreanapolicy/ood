#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Command/CChangeTitleCommand/CChangeTitleCommand.h"
#include "../src/Command/CInsertDocumentItemCommand/CInsertDocumentItemCommand.h"
#include "../src/Command/Exception/CWrongIndexOfItemInDocumentException/CWrongIndexOfItemInDocumentException.h"
#include "../src/Content/CImage/CImage.h"
#include "../src/Content/CParagraph/CParagraph.h"
#include "../src/Document/CConstDocumentItem/CConstDocumentItem.h"
#include "../src/Document/CDocumentItem/CDocumentItem.h"
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
		CConstDocumentItem constDocumentItem(std::make_shared<const CImage>(image));

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
				REQUIRE_THROWS_AS(CInsertDocumentItemCommand(firstParagraph, items, 1), CWrongIndexOfItemInDocumentException);
			}
		}
	}

	SECTION("check adding to end")
	{
		WHEN("add on 1 position, but before add at 0")
		{
			CInsertDocumentItemCommand(firstParagraph, items, 0).Execute();

			THEN("first item will be paragraph with `hello`")
			{
				REQUIRE(items.size() == 1);
				REQUIRE(items[0].GetParagraph()->GetText() == "hello");
			}

			THEN("add to end")
			{
				REQUIRE_NOTHROW(CInsertDocumentItemCommand(firstParagraph, items, items.size()));
			}
		}
	}

	SECTION("check adding and removing elements")
	{
		WHEN("add 1 paragraph")
		{
			CInsertDocumentItemCommand insertDocumentItemCommand(firstParagraph, items, 0);
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
			CInsertDocumentItemCommand insertDocumentItemCommand(image, items, 0);
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