/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "utils/Bootstrap.h"

int main(int argc, char **argv)
{
    return Bootstrap::instance()->init(argc, argv);
}

