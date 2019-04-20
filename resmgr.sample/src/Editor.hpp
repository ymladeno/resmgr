/*
 * Editor.hpp
 *
 *  Created on: Mar 15, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_SAMPLE_SRC_EDITOR_HPP_
#define RESMGR_SAMPLE_SRC_EDITOR_HPP_

#include <string>
#include <map>

class Editor {
public:
	Editor();
	virtual ~Editor();
	void set_font_color(const std::string& p_font_color);
	void set_background_color(const std::string& p_background_color);

	const std::string prefix() const {
	    return m_prefix;
	}

	const std::string postfix() const {
	    return RESET_COLOR;
	}

	bool is_colorful() const {
		return !m_prefix.empty();
	}

private:
	std::map<std::string, std::string> m_font_color = {
        {"black",   "\u001b[30m"},
        {"red",     "\u001b[31m"},
        {"green",   "\u001b[32m"},
        {"yellow",  "\u001b[33m"},
        {"blue",    "\u001b[34m"},
        {"magenta", "\u001b[35m"},
        {"cyan",    "\u001b[36m"},
        {"White",   "\u001b[37m"},
	};

    std::map<std::string, std::string> m_background_color = {
        {"black",   "\u001b[40m"},
        {"red",     "\u001b[41m"},
        {"green",   "\u001b[42m"},
        {"yellow",  "\u001b[43m"},
        {"blue",    "\u001b[44m"},
        {"magenta", "\u001b[45m"},
        {"cyan",    "\u001b[46m"},
        {"White",   "\u001b[47m"},
    };

    static constexpr const char* RESET_COLOR = "\u001b[0m";

    std::string m_prefix;
};

#endif /* RESMGR_SAMPLE_SRC_EDITOR_HPP_ */
