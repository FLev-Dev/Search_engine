# Search engine
A project created during the c++ course for training.

Performs search on json documents and saves the result as a file.

# Compiling
You need: 
* C++17 compliant compiler
* CMake build system

 ***NOTE:*** If you are using Linux, you need to change the RESOURCES_PATH and FILES_PATH variables in Converter_JSON.h. You should also use alternative terminal commands.
  
`$ git clone https://github.com/FLev-Dev/Search_engine`

`$ cd Search_engine`

`$ mkdir build && cd build`

`cmake ..` or if u use MinGW compiler use `cmake .. -G "MinGW Makefiles"`

`cmake --build .`

# Running
1. `$ cd Search_engine\resourses && config.json`
1. Change field `"max_responses":`.
2. Place your files names after `"files": [`
4. Add your requests in request.json.
5. `$ mkdir "files for search" && cd "files for search"`
   Place files at folder ***files for search***
   
    ***NOTE:*** Requests and file contents must be words of lowercase Latin letters separated by a space.

6. Start the programm. 
   
    `$ cd Search_engine\build\src && search_engine`

   ***NOTE:*** If u use Visual Studio file search_engine.exe can be at Search_engine\build\src\debug.
               Is this case change RESOURSES_PATH and FILES_PATH variables at file *Converter_JSON.h*
               then compile project again.
   
7. The results will be in the answer.json file (resources folder).



# Screenshots of the files

![](https://sun9-37.userapi.com/impg/WXS6bbU95Ll_I4IAUzwweS0oq1N69JWlGtICYw/8Xqt_rYyOUU.jpg?size=874x840&quality=96&sign=4b249976a8216052f0a75f3d8e4603a4&type=album)
![](https://sun119-2.userapi.com/impg/B7bAJuD1dccnaSyXlakzFwQw3bDITUgzNRlBKQ/M3F0XH9oykc.jpg?size=874x840&quality=96&sign=7310f20d9b8e7d2d0170c91a9b076c5b&type=album)
