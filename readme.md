# Search engine
A project created during the training process for testing.

Performs a custom search on json documents and saves the result to a file.

# Compiling
You need: 
* C++17 compliant compiler
* CMake build system


  
`$ git clone https://github.com/FLev-Dev/Search_engine`

`$ cd Search_engine`

`$ mkdir build/ && cd build/`

`cmake .. -G "MinGW Makefiles"`

`cmake --build .`

# How to work
1. `$ cd Search_engine && cd resourses && config.json`
1. Change field `"max_responses":`.
2. Place your files names after `"files": [`
4. Add your requests in request.json.
5. Place files at folder ***files for search***
***NOTE:*** Requests and file contents must be words of lowercase Latin letters separated by a space.
6. Start the programm. ~~U can just open search_engine file.~~
   
    `$ cd Search_engine && cd build && cd src`

    `$  search_engine`
7. The results will be in the answer.json file (resources folder).

# Screenshots of the files

![](https://sun9-37.userapi.com/impg/WXS6bbU95Ll_I4IAUzwweS0oq1N69JWlGtICYw/8Xqt_rYyOUU.jpg?size=874x840&quality=96&sign=4b249976a8216052f0a75f3d8e4603a4&type=album)
![](https://sun119-2.userapi.com/impg/B7bAJuD1dccnaSyXlakzFwQw3bDITUgzNRlBKQ/M3F0XH9oykc.jpg?size=874x840&quality=96&sign=7310f20d9b8e7d2d0170c91a9b076c5b&type=album)
