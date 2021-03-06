// Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "inst_util.h"
#include "chromeos_install_config.h"
#include "chromeos_legacy.h"
#include "chromeos_postinst.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string;

const char* usage = (
    "cros_installer:\n"
    "   --help\n"
    "   cros_installer postinst <mount_point> <rood_dev>\n");

int showHelp() {
  printf("%s", usage);
  return 1;
}

int main(int argc, char** argv) {

  struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0},
  };

  while (true) {
    int option_index;
    int c = getopt_long(argc, argv, "h", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
      case '?':
        // Unknown argument
        printf("\n");
        return showHelp();

      case 'h':
        // --help
        return showHelp();

      default:
        printf("Unknown argument %d - switch and struct out of sync\n\n", c);
        return showHelp();
    }
  }

  if (argc - optind < 1) {
    printf("No command type present (postinst, etc)\n\n");
    return showHelp();
  }

  string command = argv[optind++];

  // Run postinstall behavior
  if (command == "postinst") {
    if (argc - optind != 2)
      return showHelp();

    string install_dir = argv[optind++];
    string install_dev = argv[optind++];

    // ! converts bool to 0 / non-zero exit code
    return !RunPostInstall(install_dev, install_dir);
  }

  printf("Unknown command: '%s'\n\n", command.c_str());
  return showHelp();
}
