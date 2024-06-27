Ray Tracing in One Weekend Book Series
====================================================================================================

| ![RT in One Weekend][cover1] | ![RT The Next Week][cover2] | ![RT The Rest of Your Life][cover3] |
|:----------------------------:|:---------------------------:|:-----------------------------------:|
|   [In One Weekend][book1]    |   [The Next Week][book2]    |   [The Rest of Your Life][book3]    |


Getting the Books
------------------
The _Ray Tracing in One Weekend_ series of books are now available to the public for free directly
from the web.

We are currently hosting both the older v3.2.3 version and the latest v4.0.0-alpha.2 versions in the
same project. The older v3 version (really v3.2.3) is provided for readers who are in the middle of
going through the series so you can maintain continuity. For new readers, or readers newly starting
one of the books, we strongly recommend that you jump aboard the v4 train.

### Version 3.2.3
  - [Ray Tracing in One Weekend][web1-v3]
  - [Ray Tracing: The Next Week][web2-v3]
  - [Ray Tracing: The Rest of Your Life][web3-v3]

### Version 4.0.0-alpha.2

  - [Ray Tracing in One Weekend][web1]
  - [Ray Tracing: The Next Week][web2]
  - [Ray Tracing: The Rest of Your Life][web3]

These books have been formatted for both screen and print. For more information about printing your
own copies, or on getting PDFs of the books, see [PRINTING.md][] for more information.


Contributing
-------------
If you'd like to contribute a PR _**please read our [contribution guidelines][CONTRIBUTING]
first**_.


Project Status
---------------
Ok, v4.0.0-alpha.2 is finally out the door, and we are now heads down on getting the final v4.0.0
version complete and shipped by SIGGRAPH 2024, July 28. At present, that means we are largely
focused on _Ray Tracing: The Rest of Your Life_ — the third book in the series.

**v4.0.0-alpha.2 is released.** Books one and two are largely complete, and we're now focusing on
book three. You can find it at the regular spot: https://raytracing.github.io. We are temporarily
preserving the final version of v3.2.3 inside the repo, so you can just grab the latest and
reference both versions.

If you'd like to check out the latest updates and watch our progress, we're on the `dev` branch. You
can also browse our release backlog to see what we're planning. Our relevant milestones are

  - [v4.0.0](https://github.com/RayTracing/raytracing.github.io/milestone/16)
  - [v4.0.0-release](https://github.com/RayTracing/raytracing.github.io/milestone/19)

If you're interested in contributing, email us! You can find our contact info at the head of each
book. Or just start [a new discussion][discussions] or [issue][issues].


GitHub Discussions
------------------
Do you have general questions about raytracing code, issues with your own implmentation, or general
raytracing ideas you'd like to share? Check out our [GitHub discussions][discussions] forum!


Directory Structure
-------------------
The organization of this repository is meant to be simple and self-evident at a glance:

  - `books/` --
    This folder contains the three raytracing books (in HTML), and some supporting material.

  - `images/` --
    Contains all of the images and figures of the books. Can also be used to compare your
    results.

  - `style/` --
    Contains the css for the books and the site.

  - `src/` --
    Contains the source.

  - `src/<book>/` --
    Contains the final source code for each book.

  - `v3/` --
    All content (same general structure) for the v3.2.3 release (from December 2020).

  - `v3/common` --
    Contains v3 headers that are common to two or more v3 books. This is also where external headers
    are stored.


Source Code
-----------
### Intent
This repository is not meant to act as its own tutorial. The source is provided so you can compare
your work when progressing through the book. We strongly recommend reading and following along with
the book to understand the source. Ideally, you'll be developing your own implementation as you go,
in order to deeply understand how a raytracer works.

### Downloading The Source Code
The [GitHub home][] for this project contains all source and documentation associated with the _Ray
Tracing in One Weekend_ book series. To clone or download the source code, see the green "Clone or
download" button in the upper right of the project home page.

### Programming Language
This book is written in C++, and uses some modern features of C++11. The language and features were
chosen to be broadly understood by the largest collection of programmers. It is not meant to
represent ideal (or optimized) C++ code.

### Implementations in Other Languages
The _Ray Tracing in One Weekend_ series has a long history of implementations in other programming
languages (see [_Implementations in Other Languages_][implementations]), and across different
operating systems. Feel free to add your own implementation to the list!

### Branches
In general, ongoing development, with all of the latest changes, can be found in the `dev` branch,
which may contain patch, minor and major changes, depending on the release in progress. We try to
keep CHANGELOG.md up to date, so you can easily browse what's new in each development branch. We may
from time to time use additional development branches, so stay up to date by reviewing the
[CONTRIBUTING][] page.

The `release` branch contains the latest released (and live) assets. This is the branch from which
GitHub pages serves up https://raytracing.github.io/.


Building and Running
---------------------
Copies of the source are provided for you to check your work and compare against. If you wish to
build the provided source, this project uses CMake. To build, go to the root of the project
directory and run the following commands to create the debug version of every executable:

    $ cmake -B build
    $ cmake --build build

You should run `cmake -B build` whenever you change your project `CMakeLists.txt` file (like when
adding a new source file).

You can specify the target with the `--target <program>` option, where the program may be
`inOneWeekend`, `theNextWeek`, `theRestOfYourLife`, or any of the demonstration programs. By default
(with no `--target` option), CMake will build all targets.

    $ cmake --build build --target inOneWeekend

### Optimized Builds
CMake supports Release and Debug configurations. These require slightly different invocations
across Windows (MSVC) and Linux/macOS (using GCC or Clang). The following instructions will place
optimized binaries under `build/Release` and debug binaries (unoptimized and containing debug
symbols) under `build/Debug`:

On Windows:

```shell
$ cmake -B build
$ cmake --build build --config Release  # Create release binaries in `build\Release`
$ cmake --build build --config Debug    # Create debug binaries in `build\Debug`
```

On Linux / macOS:

```shell
# Configure and build release binaries under `build/Release`
$ cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
$ cmake --build build/Release

# Configure and build debug binaries under `build/Debug`
$ cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build/Debug
```

We recommend building and running the `Release` version (especially before the final render) for
the fastest results, unless you need the extra debug information provided by the (default) debug
build.

### CMake GUI on Windows
You may choose to use the CMake GUI when building on windows.

1. Open CMake GUI on Windows
2. For "Where is the source code:", set to location of the copied directory. For example,
   `C:\Users\Peter\raytracing.github.io`.
3. Add the folder "build" within the location of the copied directory. For example,
   `C:\Users\Peter\raytracing.github.io\build`.
4. For "Where to build the binaries", set this to the newly-created "build" directory.
5. Click "Configure".
6. For "Specify the generator for this project", set this to your version of Visual Studio.
7. Click "Done".
8. Click "Configure" again.
9. Click "Generate".
10. In File Explorer, navigate to build directory and double click the newly-created `.sln` project.
11. Build in Visual Studio.

If the project is succesfully cloned and built, you can then use the native terminal of your
operating system to simply print the image to file.

### Running The Programs

You can run the programs by executing the binaries placed in the build directory:

    $ build\Debug\inOneWeekend > image.ppm

or, run the optimized version (if you compiled with the release configuration):

    $ build\Release\inOneWeekend > image.ppm

The generated PPM file can be viewed directly as a regular computer image, if your operating system
supports this image type. If your system doesn't handle PPM files, then you should be able to find
PPM file viewers online. We like [ImageMagick][].


Corrections & Contributions
----------------------------
If you spot errors, have suggested corrections, or would like to help out with the project,
_**please review the [CONTRIBUTING][] document for the most effective way to proceed.**_



[book1]:           books/RayTracingInOneWeekend.html
[book2]:           books/RayTracingTheNextWeek.html
[book3]:           books/RayTracingTheRestOfYourLife.html
[CONTRIBUTING]:    CONTRIBUTING.md
[cover1]:          images/cover/CoverRTW1-small.jpg
[cover2]:          images/cover/CoverRTW2-small.jpg
[cover3]:          images/cover/CoverRTW3-small.jpg
[discussions]:     https://github.com/RayTracing/raytracing.github.io/discussions/
[GitHub home]:     https://github.com/RayTracing/raytracing.github.io/
[ImageMagick]:     https://imagemagick.org/
[implementations]: https://github.com/RayTracing/raytracing.github.io/wiki/Implementations
[issues]:          https://github.com/RayTracing/raytracing.github.io/issues/
[milestone 16]:    https://github.com/RayTracing/raytracing.github.io/milestone/16
[milestone 19]:    https://github.com/RayTracing/raytracing.github.io/milestone/19
[PRINTING.md]:     PRINTING.md
[v3.2.3]:          https://github.com/RayTracing/raytracing.github.io/releases/tag/v3.2.3
[web1]:            https://raytracing.github.io/books/RayTracingInOneWeekend.html
[web2]:            https://raytracing.github.io/books/RayTracingTheNextWeek.html
[web3]:            https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html
[web1-v3]:         https://raytracing.github.io/v3/books/RayTracingInOneWeekend.html
[web2-v3]:         https://raytracing.github.io/v3/books/RayTracingTheNextWeek.html
[web3-v3]:         https://raytracing.github.io/v3/books/RayTracingTheRestOfYourLife.html
