#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <rapidjson/document.h>
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim);
std::string extract_uuid(char *url);
std::string get_episodes(std::string uuid);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "\nUsage : ./main URL\n"
                  << std::endl;
    }
    else
    {
        std::string res_uuid = extract_uuid(argv[1]);

        std::string json = get_episodes(res_uuid);

        rapidjson::Document doc;
        doc.Parse(json.c_str());

        for (int i = 0; i < doc["count"].GetInt(); i++)
        {
            //[0]["info"]["original_torrent_ur"].GetString()
            std::cout << doc["results"][i]["episodes"][0]["name"].GetString() << std::endl;
            std::cout << doc["results"][i]["episodes"][0]["info"]["original_torrent_url"].GetString() << std::endl
                      << std::endl;
        }
    }

    return 0;
}

//split strings with a char delimiter and return a vector of strings
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

std::string extract_uuid(char *url)
{
    std::string resurl = url;
    std::vector<std::string> res = split(url, *"/anime/");

    if (res.size() < 4)
    {
        std::cout << "Error: URL incorrect" << std::endl;
        exit(0);
    }

    return res[4];
}

std::string get_episodes(std::string uuid)
{
    std::string url = "https://ssanime.ga/api/episodetitle/?page_size=1000&anime__uuid=" + uuid + "&ordering=-title&expand=links,links.site,episodes,episodes.info,episodes.torrent_files,episodes.torrent_files.short_urls&omit=id,anime,anime_picture,anime_uuid";
    std::stringstream ss;
    try
    {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::WriteStream(&ss));
        request.perform();
    }
    catch (curlpp::LogicError &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError &e)
    {
        std::cout << e.what() << std::endl;
    }

    return ss.str();
}