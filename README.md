# pathstr
### _A small library for handling filesystem paths as strings (Qt)._
The library performs generic operations with the file system paths, processing them as strings.
More suitable for handling a large number of strings/paths than stock functions do (QFile/QFileInfo/QDir).\
In some cases, it performs common operations much faster, and also has more convenient handling of common exceptions.

#### For example:
* Concatenate path strings, checking for absence of separator duplication.
* Get the folder name or the parent folder path regardless of the separator at the end of the path.

### The project purpose:
Creation of a minimalist tool, which is superior in speed and capabilities of stock Qt functions.

### Key features:
* Joining paths. Automatic check of the separator presence.
* Getting a relative path.
* Changing the file extension.
* Obtaining a parent folder. Even if the path ends with the slash.
* Checking a match of the file extension with the listed ones.

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

QString fooName = pathstr::entryName("/home/fooFolder/"); // -> "fooFolder"

QString newFile = pathstr::setSuffix("file.txt", "zip");  // -> "file.zip"

QString fullPath = pathstr::joinPath("/absolutePath", "addPath"); // -> "/absolutePath/addPath"

QString relPath = pathstr::relativePath("/rootFolder", "/rootFolder/folder2/file"); // -> "folder2/file"

```

