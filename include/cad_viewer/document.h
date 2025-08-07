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
#ifndef CAD_VIEWER_DOCUMENT_H_INCLUDED
#define CAD_VIEWER_DOCUMENT_H_INCLUDED

#include <QObject>
#include <Standard_Handle.hxx>

class TDocStd_Document;

namespace cad_viewer {

class Document : public QObject
{
  Q_OBJECT
public:
  explicit Document(Handle(TDocStd_Document) doc, QObject* parent = nullptr);
  ~Document();

  [[nodiscard]] QString name() const;

  Document(const Document&)            = delete;
  Document& operator=(const Document&) = delete;

private:
  Handle(TDocStd_Document) m_doc;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_DOCUMENT_H_INCLUDED
