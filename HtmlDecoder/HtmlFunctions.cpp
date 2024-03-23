#include "HtmlFunctions.h"

std::unordered_map<std::string, std::string> html_codes{
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
};

std::string HtmlDecode(std::string const& html)
{
	std::string decoded_html;
	size_t amp_pos = html.find("&");
	size_t pos = 0;

	while (amp_pos != std::string::npos)
	{
		decoded_html.append(html, pos, amp_pos - pos);

		auto it = html_codes.begin();
		for (; it != html_codes.end(); it++)
		{
			if (html.substr(amp_pos, it->first.length()) == it->first)
			{
				decoded_html.append(it->second);
				pos = amp_pos + it->first.length();
				break;
			}
		}

		if (it == html_codes.end())
		{
			decoded_html.append("&");
			pos = amp_pos + 1;
		}

		amp_pos = html.find("&", pos);
	}

	decoded_html.append(html, pos, html.length());
	return decoded_html;
}