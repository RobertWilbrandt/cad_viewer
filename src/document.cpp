// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-06
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/document.h"

#include <TDF_Tool.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>

namespace cad_viewer {

Document::Document(Handle(TDocStd_Document) doc, QObject* parent)
  : QObject{parent}
  , m_doc{std::move(doc)}
{
  TDataStd_Name::Set(m_doc->Main(), "New Document");

  TDF_Tool::DeepDump(std::cout, m_doc->Main());
}

Document::~Document()
{
  m_doc->Close();
}

} // namespace cad_viewer
