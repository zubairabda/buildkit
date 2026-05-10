#include <stdio.h>
#include <time.h>

#define BUILDKIT_IMPLEMENTATION
#include "buildkit.h"

int main(void)
{
    clock_t begin = clock();
    StringArray *sources = string_array_alloc(100, 32768);
    add_files(sources, "src/*.c");
    BuildRule cc_rule = build_rule("clang -c -O0 -g -I./include {in} -o {out}", ".o");
    BuildRule out_rule = build_rule("clang {in} -o {out}", ".exe");
    BuildOptions opt = {0};
    StringArray *include_paths = string_array_alloc(10, 1024);
    string_array_push(include_paths, "include");
    opt.include_paths = include_paths;
    opt.cc_rule = cc_rule;
    opt.output_rule = out_rule;
    //opt.output_dir = "bin";
    opt.dependency_kind = DEPS_KIND_SCAN;
    opt.generate_compile_commands = 1;
    build_target("test", sources, &opt);
    float elapsed = (float)(clock() - begin) / CLOCKS_PER_SEC;
    printf("Build time: %.2f\n", elapsed);
    
    return 0;
}

