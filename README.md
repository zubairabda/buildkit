# Buildkit

Buildkit is a header-only, "build system" written in C. How it works is that the build system is first bootstrapped by compiling a C application that describes the project details, then the resulting executable is ran which builds the actual project and does whatever else is required such as making directories, cleaning build artifacts, generating files, and so on.

The motivation for this project was my desire for simplifying the build process for C/C++ applications (though Buildkit can be used to build other types of projects as well), which can be a frustrating process given how simple the task should be. I also wanted more control over the build process, and since we have the capabilities of C at our disposal, the possibilities are numerous.

## Disclaimer

Buildkit probably shouldn't be used for a production grade project, and not even your hobby ones, at least not without some modification. This was made for my own projects, so I made Buildkit with assumptions pertaining to my own workflow, so keep that in mind. That being said, I tried my best to keep it as simple as possible, as you can see with some sample code.

## Usage

The basic gist of using Buildkit is as follows:
1. Define a list of source files that we want to use as **input** for the build process
2. Configure the build options, which contain some fields needed to build the project such as:
    1. **Build rules**, which are simple string tuples that state the command ran for each input file, along with the desired file extension of the output file
    2. Any include paths the project uses which are scanned for header include dependencies
    3. The output directory where the final output will be placed
3. Compile and run the build file, which will build your project files, and you're done

```c
int main(void)
{
    StringArray *sources = string_array_alloc(1024); // allocate a string pool for our source file names
    add_files(sources, "src/*.c"); // add source files to our list, supports globbing!
    BuildRule cc_rule = build_rule("cc -c {in} -o {out}", ".o"); // define the input rule
    BuildRule out_rule = build_rule("cc {in} -o {out}", NULL); // define the output rule
    BuildOptions opt = {0};
    opt.cc_rule = cc_rule;
    opt.output_rule = out_rule;
    opt.dependency_kind = DEPS_KIND_SCAN; // only supported option for now

    build_target("test", sources, &opt);

    return 0;
}
```
See the included files in this repository for an example application that can be built using Buildkit.

