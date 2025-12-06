# pathstr
### _A small library for handling filesystem paths as strings (Qt)._
The library performs generic operations with the file system paths, processing them as strings.
More suitable for handling a large number of strings/paths than stock functions do (QFile/QFileInfo/QDir).\
In some cases, it performs common operations much faster, and also has more convenient handling of common exceptions.

#### For example:
* Concatenate path strings, checking for absence of separator duplication.
* Get the folder name or the parent folder path regardless of the separator at the end of the path.

### The project purpose:
Creation of a minimalist tool with a focus on increased performance and predictability.

### Key features:
* Joining paths. Automatic check of the separator presence.
* Getting relative path.
* Changing the file extension.
* Changing the file name, keeping the path and suffix unchanged.
* Obtaining a parent folder. Even if the path ends with a slash.
* Checking a match of the file extension with the listed ones.
* Obtaining the name of the file system entry, excluding the path.

### Usage
Integration as a submodule can be used:
```
git submodule add https://github.com/artemvlas/pathstr <path-to-submodule>
```

and add to the main project's _CMakeLists.txt_ file:
```
add_subdirectory(pathstr)
```

Then in the code:
```
#include "pathstr.h"
using namespace pathstr;

QString fooName = entryName("/home/fooFolder/"); // -> "fooFolder"

QString newSuffix = setSuffix("file.txt", "zip"); // -> "file.zip"

QString newFile = renameFile("folder/file.docx", "newFile"); // -> folder/newFile.docx

QString fullPath = joinPath("/absolutePath", "addPath"); // -> "/absolutePath/addPath"

QString relPath = relativePath("/rootFolder", "/rootFolder/folder2/file"); // -> "folder2/file"

bool has_suffix = hasExtension("file.txt", {"jpg", "txt", "json"}); // -> true

```

