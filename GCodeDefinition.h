#ifndef GCODE_GCODEDEFINITION_H__
#define GCODE_GCODEDEFINITION_H__

typedef enum _GCodeType {
  G00,
  G01,
  G02,
  G03,
  G04,
  G40,
  G41,
  G42,
  G20,
  G21,
  G26,
  G27,
  G28,
  G90,
  G91,
  G92,
  G99,
  M00,
  M02,
  M07,
  M08,
  M09,
  M10,
  M11,
  M12,

} GCodeType;

typedef struct _GCodeStruct {
  unsigned int ShowLine;
  unsigned int LineNoInTotalFile;
  unsigned short Name;
  unsigned short PierceHoleNum;
  unsigned short CycleCount;
  double X0;
  double Y0;
  double X;
  double Y;
  double I;
  double J;
  double F;
  double R;
  double StartAngle;
  double EndAngle;
  double Delay;
  double KerfValue;
  double Length; // current g code line length
  double AngleRatio; // 末点切向和下一句曲线切向的夹角的变化率 
  double ScaleFactor;
  double RotateAngle;
  double HorizonMirror;
  double VerticalMirror;
} GCodeStruct;

#endif // GCODE_GCODEDEFINITION_H__
