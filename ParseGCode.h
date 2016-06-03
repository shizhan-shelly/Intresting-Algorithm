#include <vector>

#include "./FittingMethod/D_Point.h"
#include "GCodeType.h"

// This is a tool class.
class ParseGCode {
 public:
  bool ReadGCodeFile(const std::string &file,
                     std::vector<std::string> &code_lines);

  bool LinearFittingGCode(const std::vector<std::string> &code_lines,
                                 std::vector<std::string> &dest_lines);

  bool WriteGCodeFile(const std::string &file,
                      const std::vector<std::string> &code_lines);

 private:
  bool IsLinearFitting(const std::string &code);
  bool IsMotionCode(const std::string &code);
  D_Point GetTracePoint(const std::string &code);
  std::string GCodeGenerate(GCodeType g_type, D_Point points);

  D_Point cur_point_;


}; //  class ParseGCode
