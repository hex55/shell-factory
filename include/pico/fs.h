#ifndef PICOLIB_IO_H_
#define PICOLIB_IO_H_

namespace Pico {

    namespace Filesystem {

        class File : public BasicStream
        {
            public:
                constexpr static int READ       = (1 << 0);
                constexpr static int WRITE      = (1 << 1);
                constexpr static int APPEND     = (1 << 2);
                constexpr static int TRUNCATE   = (1 << 3);

                FUNCTION File   open(const char *path, int flags);
                FUNCTION File   create(const char *path, int flags, mode_t mode);
                FUNCTION int    remove(const char *path);
                FUNCTION size_t size(const char *path);

                NO_RETURN METHOD void execute(char *const argv[] = nullptr, char *const envp[] = nullptr);
                METHOD size_t   size();

                CONSTRUCTOR     File(const char *path, int flags = READ|WRITE, bool create = false, mode_t mode = 0700);
        };

        class Directory : public SingleIO
        {
            public:
                using SingleIO::SingleIO;

                FUNCTION        Directory open(const char *path);
                FUNCTION int    create(const char *path, mode_t mode);
                FUNCTION int    remove(const char *path);

                template <typename Func>
                FUNCTION int    each(const char *path, Func);
                FUNCTION int    set_current(const char *path);
                FUNCTION int    get_current(char *path, size_t size);
                FUNCTION int    change_root(const char *path);

                CONSTRUCTOR Directory(const char *path);

                template <typename Func>
                METHOD int      list(Func);
                METHOD int      set_current();
        };
    }
}

#endif
