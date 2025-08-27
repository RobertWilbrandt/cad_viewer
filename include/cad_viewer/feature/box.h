// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-26
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_FEATURE_BOX_H_INCLUDED
#define CAD_VIEWER_FEATURE_BOX_H_INCLUDED

#include <Standard_Handle.hxx>
#include <TFunction_Driver.hxx>
#include <optional>

namespace cad_viewer::feature {

class Box : public TFunction_Driver
{
public:
  Standard_Integer Execute(Handle(TFunction_Logbook) & log) const override;

  void Arguments(TDF_LabelList& args) const override;
  void Results(TDF_LabelList& res) const override;

private:
  std::optional<TDF_Label> findProperty(const TDF_Label& label, const std::string& name) const;
  std::optional<double> evaluateProperty(const TDF_Label& label) const;
};

} // namespace cad_viewer::feature

#endif // CAD_VIEWER_FEATURE_BOX_H_INCLUDED
