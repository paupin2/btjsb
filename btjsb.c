/*!
 * btjsb - build-time javascript bundler
 * http://github.com/alfred300p/btjsb
 *
 * Copyright 2015, Paulo Pinto
 * Released under the Apache 2.0 license
 * http://www.apache.org/licenses
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 4096
#define MAX_MATCHES 5
#define die(...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); exit(1); } while (0)

regmatch_t matches[MAX_MATCHES];
regex_t re_include;

void parse_file(const char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		die("could not open: %s", filename);
	}

	int line_nr = 0;
	char line[MAX_LINE_LENGTH];
	char dependency[MAX_LINE_LENGTH];
	while ((fgets(line, MAX_LINE_LENGTH, f)) != NULL) {
		line_nr += 1;
		if (regexec(&re_include, line, MAX_MATCHES, matches, 0) == 0) {
			// build dependency filename, deal with relative paths
			line[matches[1].rm_eo] = '\0'; // end
			const char *slash = strrchr(filename, '/');
			if (slash) {
				// current filename contains a path
				snprintf(dependency, MAX_LINE_LENGTH, "%.*s%s", (int)(slash - filename + 1), filename, line + matches[1].rm_so);
			} else {
				snprintf(dependency, MAX_LINE_LENGTH, "%s", line + matches[1].rm_so);
			}

			printf("// %s:%d includes %s\n", filename, line_nr, dependency);
			parse_file(dependency);
			printf("// end of %s, back to %s:%d\n", dependency, filename, line_nr);
		} else {
			// regular line
			printf("%s", line);
		}
	}
	printf("\n");
}

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		// usage
		fprintf(stderr, "usage: btjsb file.js # concatenate file and includes and print to the standard output\n");
		exit(2);
	}

	// parse lines like: include("relative/path.js");
	if (regcomp(&re_include, "^[ \t]*include[ \t]*\\([ \t]*[\"']([-_./a-z0-9]+\\.js)[\"'][ \t]*\\)[ \t]*;?[ \t]*$", REG_EXTENDED|REG_ICASE|REG_NEWLINE) != 0) {
	// if (regcomp(&re_include, "^[ \t]*include.*", REG_EXTENDED|REG_ICASE|REG_NEWLINE) != 0) {
		die("error compiling regex");
	}

	parse_file(argv[1]);

	return 0;
}
