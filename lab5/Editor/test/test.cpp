#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Content/CImage/CImage.h"
#include "../src/Content/CParagraph/CParagraph.h"
#include "../src/Document/CDocumentItem/CDocumentItem.h"
#include "../src/Document/CConstDocumentItem/CConstDocumentItem.h"
#include "../src/History/CHistory/CHistory.h"
#include "../test/Command/CTestCommand/CTestCommand.h"
#include "../src/Command/CChangeTitleCommand/CChangeTitleCommand.h"
#include "../src/Command/CReplaceTextParagraphCommand/CReplaceTextParagraphCommand.h"

TEST_CASE("check creation image")
{
	SECTION("construction with exceptions(wrong extention)")
	{
		REQUIRE_THROWS_AS(CImage("hello.js", 200, 200), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(file does not exist)")
	{
		REQUIRE_THROWS_AS(CImage("hello.png", 200, 200), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(wrong size)")
	{
		REQUIRE_THROWS_AS(CImage("../test/image.png", 0, 200), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, -1), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, 20000), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 20000, 200), WrongImageSizeException);
	}

	SECTION("create image without exceptions")
	{
		CImage image("../test/image.png", 200, 350);

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
	SECTION("create image without exceptions")
	{
		CParagraph paragraph("hello");

		REQUIRE(paragraph.GetText() == "hello");
	}
}

TEST_CASE("test DocumentItem and ConstDocumentItem")
{
	SECTION("create DocumentItem via IImage")
	{
		CImage image("../test/image.png", 200, 200);
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
		CParagraph paragraph("hello");
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
		CImage image("../test/image.png", 200, 200);
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
		CParagraph paragraph("hello");
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