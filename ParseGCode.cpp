#include "ParseGCode.h"

#include <assert.h>

#include <fstream>
#include <string>

#include "./FittingMethod/LinearFitting.h"

bool ParseGCode::ReadGCodeFile(const std::string &file,
                               std::vector<std::string> &code_lines) {

  std::ifstream in_file(file.c_str());
  if (!in_file) {
    return false;
  }
  std::string line_text = "";
  while (getline(in_file, line_text)) {
    code_lines.push_back(line_text);
  }

  in_file.close();
  in_file.clear();

  return true;
}

bool ParseGCode::WriteGCodeFile(const std::string &file,
                                const std::vector<std::string> &code_lines) {

  std::ofstream out_file(file.c_str());
  if (!out_file) {
    return false;
  }
  for (size_t i = 0; i < code_lines.size(); i++) {
    out_file << code_lines[i];
  }
  out_file.close();
  out_file.clear();
  return true;
}

bool ParseGCode::LinearFittingGCode(const std::vector<std::string> &code_lines,
                                    std::vector<std::string> &dest_lines) {

  assert(!code_lines.empty());
  cur_point_ = D_Point(0., 0.);
  std::vector<D_Point> fitting_points;
  for (size_t i = 0; i < code_lines.size(); i++) {
    if (IsLinearFitting(code_lines[i])) {
      if (fitting_points.empty()) {
        fitting_points.push_back(cur_point_);
      }
      fitting_points.push_back(GetTracePoint(code_lines[i]));
    } else {
      if (!fitting_points.empty()) {
        LinearFitting fitter;
        std::vector<D_Point> new_points;
        fitter.CurveFitting(fitting_points, new_points);
        fitting_points.clear();
        for (size_t j = 0; j < new_points.size(); j++) {
          dest_lines.push_back(GCodeGenerate(G01, new_points[j]));
        }
      }
      dest_lines.push_back(code_lines[i] + "\n");
    }
    if (IsMotionCode(code_lines[i])) {
      cur_point_ = GetTracePoint(code_lines[i]);
    }
  }
  return true;
}

bool ParseGCode::IsLinearFitting(const std::string &code) {
  if (code.find("G01") != std::string::npos) {
    D_Point trace_point = GetTracePoint(code);
    double length = D_Point::Distance(cur_point_, trace_point);
    if (length < 2) {
      return true;
    }
  }
  return false;
}

D_Point ParseGCode::GetTracePoint(const std::string &code) {
  size_t x_index = code.find_first_of("X");
  if (x_index != std::string::npos) {
    x_index++;
  }
  size_t y_index = code.find_first_of("Y");
  if (y_index != std::string::npos) {
    y_index++;
  }

  std::string x_value = code.substr(x_index);
  char *ptr;
  double x = strtod(x_value.c_str(), &ptr);

  std::string y_value = code.substr(y_index);
  double y = strtod(y_value.c_str(), &ptr);
  return D_Point(x, y);
}

bool ParseGCode::IsMotionCode(const std::string &code) {
  static const char *MOTION[] = {"G01", "G02", "G03", "G00"};
  for (int i = 0; i < sizeof(MOTION) / sizeof(MOTION[0]); ++i) {
    if (code.find(MOTION[i]) != std::string::npos) {
      return true;
    }
  }
  return false;
}

std::string ParseGCode::GCodeGenerate(GCodeType g_type, D_Point point) {

  char buf[100];
  switch (g_type) {
   case G00:
    sprintf(buf, "G00X%.3fY%.3f\n", point.x(), point.y());
    break;
   case G01:
    sprintf(buf, "G01X%.3fY%.3f\n", point.x(), point.y());
    break;
   default:
    break;
  }
  return buf;
}
