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

#include "cad_viewer/model.h"

#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>

namespace cad_viewer {

Document::Document(Handle(TDocStd_Document) doc, QObject* parent)
  : QObject{parent}
  , m_doc{std::move(doc)}
  , m_model{new Model{m_doc->GetData(), this}}
{
  m_model->setName("New Document");
}

Document::~Document()
{
  m_doc->Close();
}

Model* Document::model() const
{
  return m_model;
}

} // namespace cad_viewer
