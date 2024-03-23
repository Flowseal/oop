#include "pch.h"
#include "../HtmlDecoder/HtmlFunctions.cpp"

TEST(HtmlDecodeTest, Empty)
{
	std::string html = "";
	std::string exp_decoded_html = "";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, NoHtmlCodes)
{
	std::string html = "Hello world";
	std::string exp_decoded_html = "Hello world";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, NoHtmlCodesWithLambda)
{
	std::string html = "Hello & world";
	std::string exp_decoded_html = "Hello & world";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, NoHtmlCodesWithSemiColon)
{
	std::string html = "Hello ; world";
	std::string exp_decoded_html = "Hello ; world";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, EmptyHtmlCode)
{
	std::string html = "Hello &; world";
	std::string exp_decoded_html = "Hello &; world";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, SingleHtmlCode)
{
	std::string html = "&amp;";
	std::string exp_decoded_html = "&";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, MultipleHtmlCodes)
{
	std::string html = "&amp;&quot;&apos;&lt;&gt;";
	std::string exp_decoded_html = "&\"'<>";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, MultipleHtmlCodesWithIncorrectCode)
{
	std::string html = "&amp;&quot;&apos;&notexists;&lt;&gt;";
	std::string exp_decoded_html = "&\"'&notexists;<>";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, MixedHtml)
{
	std::string html = "He said &quot;Hello, &notexists; &apos;World&apos;!&quot;&xo";
	std::string exp_decoded_html = "He said \"Hello, &notexists; 'World'!\"&xo";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, CapsulatedHtmlCode)
{
	std::string html = "He said &&quot&quot;&lt;;";
	std::string exp_decoded_html = "He said &&quot\"<;";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

TEST(HtmlDecodeTest, WrongHtmlCode)
{
	std::string html = "&apos is lt; when &gt&;";
	std::string exp_decoded_html = "&apos is lt; when &gt&;";

	EXPECT_EQ(HtmlDecode(html), exp_decoded_html);
}

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}