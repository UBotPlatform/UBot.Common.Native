## About UBot
UBot is an open source platform for developing chat bots. It provides consistent apis for different platforms (telegram, discord and more!) in a language-independent way, making bot development WORA-able (Write once, Run anywhere).

## About UBot.Common.Native
This library provides a lot of helper functions for writing UBot Components (~~Account / ~~App, currently this library is used to write App only) with native languages (C++, EPL and anything that supports P/Invoke).    

## Usage
Just download the released package and call the function to write your UBot Components.  
The headers for C++ and the declarations for EPL is included in the released package.  

## Build
This project uses MSBuild for building, so you can install Visual Studio 2019 for setting up the environment.  
Vcpkg is used for managing dependencies, so you can use the following command to install the dependencies:
```bash
# Note that `-static` is needed since this project always uses static libraries.
vcpkg install ixwebsocket skyr-url rapidjson --triplet x86-windows-static
```

## Reference
### String
For a native language, string is always a complex data structure. UBotNative always uses C-style strings.  
A C-style string is simply an array of characters that uses a null terminator. It's a common style for native languages, but it doesn't care about encoding. In order to meet different needs, UBotNative provides functions with different names (WindowsAPI-style) to deal with different encodings.  
- When a function with suffix `A`, it means that Windows Ansi Codepage is used.
- When a function with suffix `W`, it means that WideString (`wchar_t*`) is used. (Usually UTF-16 on Windows)
- When a function with suffix `U8`, it means that UTF-8 is used. 

In C++, the headers will implicitly create the aliases that have no suffix.  

## License
This library is licensed under BSD 3-Clause License.  
Please see [LICENSE](LICENSE.md) for licensing details.  
You can use TLDRLegal to see a [summary](https://www.tldrlegal.com/l/bsd3) first. (***!!!NOT LEGAL ADVICE!!!***)