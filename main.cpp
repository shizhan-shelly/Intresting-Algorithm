#include "./GCode/ParseGCode.h"

int main(int argc, char *argv[]) {
  ParseGCode parse;
  std::vector<std::string> code_lines;
  parse.ReadGCodeFile("d://test.txt", code_lines);
  std::vector<std::string> dst_lines;
  parse.LinearFittingGCode(code_lines, dst_lines);
  parse.WriteGCodeFile("d://new.txt", dst_lines);
  return 1;
}
