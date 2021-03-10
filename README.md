# SSAnime Scrapper
  A small scraper written in C++ to get the torrent links from ssanime.ga

## Dependencies

* [Rapidjson](https://github.com/Tencent/rapidjson)
* [Curlpp](https://github.com/jpbarrette/curlpp)

```
sudo dnf install curlpp-devel

git clone https://github.com/Tencent/rapidjson

sudo cp -r rapidjson/include/* /usr/local/include/
```
## Build Instructions

```
1. git clone https://github.com/krypton-kry/ssanime-scraper
2. cd ssanime-scraper/build
3. ./build.sh

(Please examine all bash scripts before running them;
    in this case : cat build.sh)
```
Example: ./main https://ssanime.ga/anime/2dc57a1f-2df2-47c0-9624-b83dbfbfb4c7

