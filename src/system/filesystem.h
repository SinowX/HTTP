//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_FILESYSTEM_H
#define SIHTTP_FILESYSTEM_H

#include "system/file_descriptor.h"
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <string>
#include <chrono>

#include <sys/time.h>

#include <dirent.h>

#include <map>


// 对文件系统进行操作，主要是对相关syscall和glibc函数的封装
// stat() fstat() fstatat() lstat()
// S_ISREG() S_ISDIR() S_ISCHR() S_ISBLK() S_ISFIFO() S_ISLNK() S_ISSOCK()
// S_TYPEISMQ() S_TYPEISSEM() S_TYPEISSHM() S_ISUID() S_ISGID()
// access() faccessat()
// umask()
// chmod() fchmod() fchmodat()
// chown() fchown() fchownat() lchown()
// truncate() ftruncate()
// link() linkat() unlink() unlinkat()
// remove()
// rename() renameat()
// symlink() symlinkat()
// readlink() readlinkat()
// futimes() utimensat() utimes()
// mkdir() mkdirat() rmdir()
// opendir() fdopendir() readdir() rewinddir() closedir() telldir() seekdir()
// chdir() fchdir() getcwd()
// inotify()
namespace FS {

    class FileState {
    private:
        struct stat _status;

    public:
        FileState(struct stat const &status)
                : _status(status) {}

    public:
        // ID of device containing file
        unsigned int devMajorID() const noexcept;

        unsigned int devMinorID() const noexcept;

        // if special file
        unsigned int rdevMajorID() const noexcept;

        unsigned int rdevMinorID() const noexcept;

        ino_t Inode() const noexcept;

        nlink_t hardLinkCnt() const noexcept;

        uid_t ownerUID() const noexcept;

        uid_t ownerGID() const noexcept;

        off_t totalSize() const noexcept;

        // preferred block size for efficient fs I/O
        blksize_t blockSize() const noexcept;

        // number of blocks allocated to the file, 512-byte units
        blkcnt_t blockCnt() const noexcept;

        // last access time
        std::tuple<std::chrono::seconds, std::chrono::nanoseconds>
        accessTime() const noexcept;

        // last modification change time
        std::tuple<std::chrono::seconds, std::chrono::nanoseconds>
        modifiedTime() const noexcept;

        // last status change time
        std::tuple<std::chrono::seconds, std::chrono::nanoseconds>
        changeTime() const noexcept;

        // File Type Test
        bool isRegular() const noexcept;

        bool isDirectory() const noexcept;

        bool isCharacter() const noexcept;

        bool isBlock() const noexcept;

        bool isFIFO() const noexcept;

        bool isLink() const noexcept;

        bool isSocket() const noexcept;

        // File Mode Test
        bool setUID() const noexcept;

        bool setGID() const noexcept;

        bool setSticky() const noexcept;

        // File Permission Test
        bool ownerRWX() const noexcept;

        bool ownerRd() const noexcept;

        bool ownerWr() const noexcept;

        bool ownerEx() const noexcept;

        bool groupRWX() const noexcept;

        bool groupRd() const noexcept;

        bool groupWr() const noexcept;

        bool groupEx() const noexcept;

        bool otherRWX() const noexcept;

        bool otherRd() const noexcept;

        bool otherWr() const noexcept;

        bool otherEx() const noexcept;


    };

    // state variants can all use fstatat() syscall
    FileState State(std::string const &pathname);

    FileState State(FileDescriptor const &fd);

    // if pathname abs path, fd is ignored;
    // otherwise, the file path is the pathname relative to fd
    FileState State(FileDescriptor const &fd, std::string const &pathname);

    // do not dereference link file
    FileState linkState(std::string const &pathname);

    // do not dereference link file
    FileState linkState(FileDescriptor const &fd);

    // do not dereference link file
    // if pathname abs path, fd is ignored;
    // otherwise, the file path is the pathname relative to fd
    FileState linkState(FileDescriptor const &fd, std::string const &pathname);


    class DirEntry {
    private:
        class Entry {
        public:
            ino_t Inode;
            std::string Name;
        };

        std::map<std::string, Entry> _entry{};
        std::string _dir_path{};
        DIR *_dir_stream;

        DirEntry(DIR *dir_stream) : _dir_stream(dir_stream) {}

        friend DirEntry &makeDirEntry(std::string const &pathname);

        friend DirEntry &makeDirEntry(FileDescriptor const &fd);

    public:
        ~DirEntry() {
            closedir(_dir_stream);
        }

    public:
        auto begin() { return _entry.cbegin(); }

        auto end() { return _entry.cend(); }

        // if no such file, return DirEntry.end()
        decltype(_entry.cbegin()) const operator[](std::string const &filename) const {
            return _entry.find(filename);
        }
    };

    DirEntry &makeDirEntry(std::string const &pathname);

    DirEntry &makeDirEntry(FileDescriptor const &fd);


    bool Access(bool testRead, bool testWrite, bool testExecute, std::string const &pathname);

    bool Access(bool testRead, bool testWrite, bool testExecute, FileDescriptor const &fd);

    bool Access(bool testRead, bool testWrite, bool testExecute, FileDescriptor const &fd, std::string const &pathname);

    bool linkAccess(bool testRead, bool testWrite, bool testExecute, std::string const &pathname);

    bool linkAccess(bool testRead, bool testWrite, bool testExecute, FileDescriptor const &fd);

    bool
    linkAccess(bool testRead, bool testWrite, bool testExecute, FileDescriptor const &fd, std::string const &pathname);

    // mask newly create file mode
    mode_t Mask(mode_t mask);

    mode_t Chmod(std::string const &pathname, mode_t mode);

    mode_t Chmod(FileDescriptor const &fd, mode_t mode);

    mode_t Chmod(FileDescriptor const &fd, std::string const &pathname, mode_t mode);

    mode_t linkChmod(std::string const &pathname, mode_t mode);

    mode_t linkChmod(FileDescriptor const &fd, mode_t mode);

    mode_t linkChmod(FileDescriptor const &fd, std::string const &pathname, mode_t mode);

    // return after changed owner uid and gid
    std::tuple<uid_t, gid_t> Chown(std::string const &pathname, uid_t owner, gid_t group);

    std::tuple<uid_t, gid_t> Chown(FileDescriptor const &fd, uid_t owner, gid_t group);

    std::tuple<uid_t, gid_t> Chown(FileDescriptor const &fd, std::string const &pathname, uid_t owner, gid_t group);

    std::tuple<uid_t, gid_t> linkChown(std::string const &pathname, uid_t owner, gid_t group);

    std::tuple<uid_t, gid_t> linkChown(FileDescriptor const &fd, uid_t owner, gid_t group);

    std::tuple<uid_t, gid_t> linkChown(FileDescriptor const &fd, std::string const &pathname, uid_t owner, gid_t group);

    // return after changed length
    off_t truncate(std::string const &pathname, off_t length);

    off_t truncate(FileDescriptor fd, off_t length);


    // hard link
    void Link(std::string const &targetpath, std::string const &linkpath);

    void Link(FileDescriptor const &targetdirfd, std::string const &targetpath, FileDescriptor const &linkdirfd,
              std::string const &linkpath);

    void linkLink(std::string const &targetpath, std::string const &linkpath);

    void linkLink(FileDescriptor const &targetdirfd, std::string const &targetpath, FileDescriptor const &linkdirfd,
                  std::string const &linkpath);

    // syscall unlink() unlinkat()
    // 直接调用unlinkat()，若返回 EISDIR，则再尝试使用 AT_REMOVEDIR
    void Remove(std::string const &pathname);

    void Remove(FileDescriptor const &fd, std::string const &pathname);


    // syscall renameat2()
    void Move(std::string const &oldpath, std::string const &newpath);

    void Move(FileDescriptor const &olddirfd, std::string const &oldpath, FileDescriptor const &newdirfd,
              std::string const &newpath);


    // syscall symlink2()
    void symLink(std::string const &target, std::string const &linkpath);

    void symLink(std::string const &target, FileDescriptor const &fd, std::string const &linkpath);

    // read symlink
    std::string readLink(std::string const &pathname);

    std::string readLink(FileDescriptor const &fd, std::string const &pathname);


    // utimes()
    void changeTime(std::string const &pathname, std::tuple<long, long> access, std::tuple<long long> modification);

    // futimes()
    void changeTime(FileDescriptor const &fd, std::tuple<long, long> access, std::tuple<long long> modification);

    // lutimes()
    void changeLinkTime(std::string const &pathname, std::tuple<long, long> access, std::tuple<long long> modification);


    // return path
    std::string Mkdir(std::string const &pathname, mode_t mode);

    std::string Mkdir(FileDescriptor const &fd, std::string const &pathname, mode_t mode);

    std::string getCWD() {
        char *ptr = getcwd(nullptr, 0);
        std::string res(ptr);
        free(ptr);
        return res;
    }

    // chdir()
    void changeDir(std::string const &pathname);

    // fchdir()
    void changeDir(FileDescriptor const &fd);

}


#endif //SIHTTP_FILESYSTEM_H
