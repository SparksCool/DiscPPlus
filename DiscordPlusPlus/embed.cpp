#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include <iostream>

using DiscPPlus::Embed;

void Embed::SetTitle(std::string title) {
	payload["embed"]["title"] = title;
}
void Embed::AddField(std::string name, std::string value, bool inlin) {
	nlohmann::json field;
	field["name"] = name;
	field["value"] = value;
	field["inline"] = inlin;
	payload["embed"]["fields"].push_back(field);
}
void Embed::SetColor(int color) {
	payload["embed"]["color"] = color;
}
void Embed::SetDesc(std::string desc) {
	payload["embed"]["description"] = desc;
}
void Embed::SetAuthor(std::string name, std::string url, std::string icon_url, std::string proxy_icon_url) {
	payload["embed"]["author"]["name"] = name;
	payload["embed"]["author"]["url"] = url;
	payload["embed"]["author"]["icon_url"] = icon_url;
	payload["embed"]["author"]["proxy_icon_url"] = proxy_icon_url;
}
void Embed::SetFooter(std::string text, std::string icon_url, std::string proxy_icon_url) {
	payload["embed"]["footer"]["text"] = text;
	payload["embed"]["footer"]["icon_url"] = icon_url;
	payload["embed"]["footer"]["proxy_icon_url"] = proxy_icon_url;
}

