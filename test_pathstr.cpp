#include <QtTest/QTest>

#include "pathstr.h"

class test_pathstr : public QObject
{
    Q_OBJECT

public:
    test_pathstr();
    ~test_pathstr();

private slots:
    void test_entryName();
    void test_baseName();
    void test_parentFolder();
    void test_relativePath();
    void test_joinPath();
    void test_composeFilePath();
    void test_renameFile();
    void test_root();
    void test_suffix();
    void test_completeSuffix();
    void test_setSuffix();
    void test_suffixSize();
    void test_completeSuffixSize();
    void test_isRoot();
    void test_hasExtension();
    void test_isAbsolute();
    void test_isSeparator();
    void test_endsWithSep();
    void test_startsWithSep();
    void test_appendSep();
    void test_chopSep();
};

test_pathstr::test_pathstr() {}

test_pathstr::~test_pathstr() {}

void test_pathstr::test_entryName()
{
    QCOMPARE(pathstr::entryName("/folder/file.txt"), "file.txt");
    QCOMPARE(pathstr::entryName("/folder/folder2/"), "folder2");
    QCOMPARE(pathstr::entryName("/folder/folder.3/"), "folder.3");
}

void test_pathstr::test_baseName()
{
    using namespace pathstr;
    QCOMPARE(baseName("/folder/file.txt"), "file");
    QCOMPARE(baseName("/folder/archive.tar.gz"), "archive");
    QCOMPARE(baseName("/folder.name/.archive.zip"), ".archive");
    QCOMPARE(baseName("file.name.with.dots.tar.gz"), "file.name.with.dots");
    QCOMPARE(baseName(".file.txt"), ".file");
    QCOMPARE(baseName("file_name.zip"), "file_name");
}

void test_pathstr::test_parentFolder()
{
    QCOMPARE(pathstr::parentFolder("/folder/file_or_folder2"), "/folder");
    QCOMPARE(pathstr::parentFolder("/folder/file_or_folder2/"), "/folder");
}

void test_pathstr::test_relativePath()
{
    using namespace pathstr;
    QCOMPARE(relativePath("/folder/rootFolder", "/folder/rootFolder/folder2/file"), "folder2/file");
    QCOMPARE(relativePath("/folder/rootFolder/", "/folder/rootFolder/folder2/file"), "folder2/file");
    QVERIFY(relativePath("/rootFolder/", "/rootFolder/").isEmpty());
    QVERIFY(relativePath("/rootFolder", "/rootFolder/").isEmpty());
}

void test_pathstr::test_joinPath()
{
    using namespace pathstr;
    QCOMPARE(joinPath("/home/folder", "folder2/file"), "/home/folder/folder2/file");
    QCOMPARE(joinPath("/home/folder/", "folder2/file"), "/home/folder/folder2/file");
    QCOMPARE(joinPath("/home/folder", "/folder2/file"), "/home/folder/folder2/file");
    QCOMPARE(joinPath("/home/folder", "\\folder2\\file"), "/home/folder\\folder2\\file");
    QCOMPARE(joinPath("/home/folder/", "\\folder2\\file"), "/home/folder\\folder2\\file");
    QCOMPARE(joinPath("C:\\folder\\", "\\folder2\\file"), "C:\\folder\\folder2\\file");
    QCOMPARE(joinPath("C:\\folder\\", "/folder2/file"), "C:\\folder/folder2/file");
}

void test_pathstr::test_composeFilePath()
{
    using namespace pathstr;
    QCOMPARE(composeFilePath("/home/folder", "filename", "cpp"), "/home/folder/filename.cpp");
    QCOMPARE(composeFilePath("/home/folder", ".filename", ""), "/home/folder/.filename");
    QCOMPARE(composeFilePath(QString(), "archive", "tar.gz"), "archive.tar.gz");
    QCOMPARE(composeFilePath(QString(), "archive", ""), "archive");
}

void test_pathstr::test_renameFile()
{
    using namespace pathstr;
    QCOMPARE(renameFile("file.docx", "new_name"), "new_name.docx");
    QCOMPARE(renameFile("file_name", "new_name"), "new_name");
    QCOMPARE(renameFile("/folder/archive.tar.gz", "new_name"), "/folder/new_name.tar.gz");
    QCOMPARE(renameFile("folder/archive.tar.gz", "new_name.tar.gz"), "folder/new_name.tar.gz");
    QCOMPARE(renameFile("folder/.file", "new_name"), "folder/new_name");
}

void test_pathstr::test_root()
{
    using namespace pathstr;
    QCOMPARE(root("C:/folder"), "C:/");
    QCOMPARE(root("d:\\"), "D:/");
    QCOMPARE(root("/home"), "/");
    QCOMPARE(root("/"), "/");
}

void test_pathstr::test_suffix()
{
    using namespace pathstr;
    QCOMPARE(suffix("file.txt"), "txt");
    QCOMPARE(suffix("file.ver.json"), "json");
    QCOMPARE(suffix(".hidden_file"), "");
}

void test_pathstr::test_completeSuffix()
{
    using namespace pathstr;
    QCOMPARE(completeSuffix("file.txt"), "txt");
    QCOMPARE(completeSuffix("folder/archive.tar.gz"), "tar.gz");
    QCOMPARE(completeSuffix("/folder.name/archive.tar.gz"), "tar.gz");
    QCOMPARE(completeSuffix("folder.name/file.ver.json"), "ver.json");
    QCOMPARE(completeSuffix("/folder.name/.archive.zip"), "zip");
    QCOMPARE(completeSuffix("file.name.with.dots.tar.gz"), "tar.gz");
    QCOMPARE(completeSuffix("folder/.hidden_file.txt"), "txt");
    QCOMPARE(completeSuffix("folder/.hidden_file.epub.zip"), "epub.zip");
    QVERIFY(completeSuffix(".hidden_file").isNull());
    QVERIFY(completeSuffix("folder/.1").isEmpty());
    QVERIFY(completeSuffix("folder/1.").isNull());
    QVERIFY(completeSuffix("f.").isNull());
}

void test_pathstr::test_setSuffix()
{
    using namespace pathstr;
    QCOMPARE(setSuffix("file.txt", "cpp"), "file.cpp");
    QCOMPARE(setSuffix("file.ver.json", "json"), "file.ver.json");
    QCOMPARE(setSuffix(".hidden", "txt"), ".hidden.txt");
}

void test_pathstr::test_suffixSize()
{
    using namespace pathstr;
    QCOMPARE(suffixSize("file.txt"), 3);
    QCOMPARE(suffixSize("file.ver.json"), 4);
    QCOMPARE(suffixSize(".hidden_file"), 0);
    QCOMPARE(suffixSize(".file.txt"), 3);
}

void test_pathstr::test_completeSuffixSize()
{
    using namespace pathstr;
    QCOMPARE(completeSuffixSize("file.txt"), 3);
    QCOMPARE(completeSuffixSize("file.ver.json"), 8);
    QCOMPARE(completeSuffixSize("/folder/archive.tar.gz"), 6);
    QCOMPARE(completeSuffixSize("/folder.name/archive.tar.gz"), 6);
    QCOMPARE(completeSuffixSize("folder.name/file.ver.json"), 8);
    QCOMPARE(completeSuffixSize("/folder.name/.archive.zip"), 3);
    QCOMPARE(completeSuffixSize("file.name.with.dots.tar.gz"), 6);
    QCOMPARE(completeSuffixSize("folder/.hidden_file.txt"), 3);
    QCOMPARE(completeSuffixSize("folder/.hidden_file.epub.zip"), 8);
    QCOMPARE(completeSuffixSize(".hidden_file"), 0);
    QCOMPARE(completeSuffixSize("folder/.1"), 0);
    QCOMPARE(completeSuffixSize("folder/1."), 0);
    QCOMPARE(completeSuffixSize("f."), 0);
}

void test_pathstr::test_isRoot()
{
    using namespace pathstr;
    QVERIFY(isRoot("/"));
    QVERIFY(isRoot("D:\\"));
    QVERIFY(isRoot("c:/"));
    QVERIFY(!isRoot("E:/folder"));
    QVERIFY(!isRoot("/home"));
}

void test_pathstr::test_hasExtension()
{
    using namespace pathstr;
    QVERIFY(hasExtension("file.cpp", "cpp"));
    QVERIFY(hasExtension("file.txt", ".TXT"));
    QVERIFY(hasExtension("folder/file.ver.json", "json"));
    QVERIFY(hasExtension("folder.2/file.ver.json", "ver.json"));
    QVERIFY(hasExtension("folder/.archive.tar.gz", ".tar.GZ"));
    QVERIFY(!hasExtension("file.cpp", "ver"));
    QVERIFY(hasExtension(".file.cpp", ".Cpp"));
    QVERIFY(hasExtension("file", ""));
    QVERIFY(hasExtension(".file", ""));
    QVERIFY(!hasExtension(".file", ".file"));
    QVERIFY(hasExtension("file.cpp", { "txt", "h", "cpp" }));
    QVERIFY(!hasExtension("file.cpp", { "jpg", "h", "pdf" }));
}

void test_pathstr::test_isAbsolute()
{
    using namespace pathstr;
    QVERIFY(isAbsolute("/home"));
    QVERIFY(isAbsolute("c:/folder"));
    QVERIFY(isAbsolute("D:\\file.txt"));
    QVERIFY(!isAbsolute("folder/file.txt"));
}

void test_pathstr::test_isSeparator()
{
    QVERIFY(pathstr::isSeparator('/'));
    QVERIFY(pathstr::isSeparator('\\'));
}

void test_pathstr::test_endsWithSep()
{
    QVERIFY(pathstr::endsWithSep("/folder/"));
    QVERIFY(pathstr::endsWithSep("C:\\folder\\"));
    QVERIFY(!pathstr::endsWithSep("/folder"));
}

void test_pathstr::test_startsWithSep()
{
    using namespace pathstr;
    QVERIFY(startsWithSep("/folder"));
    QVERIFY(startsWithSep("\\folder\\file.txt"));
    QVERIFY(!startsWithSep("folder/"));
    QVERIFY(!startsWithSep("C:\\folder\\"));
}

void test_pathstr::test_appendSep()
{
    QCOMPARE(pathstr::appendSep("fooFolder"), "fooFolder/");
    QCOMPARE(pathstr::appendSep("fooFolder/"), "fooFolder/");
}

void test_pathstr::test_chopSep()
{
    using namespace pathstr;
    QCOMPARE(chopSep("fooPath/"), "fooPath");
    QCOMPARE(chopSep("fooPath\\"), "fooPath");
    QCOMPARE(chopSep("fooPath"), "fooPath");
}

QTEST_APPLESS_MAIN(test_pathstr)

#include "test_pathstr.moc"
