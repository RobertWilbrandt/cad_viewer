// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-07
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/tool_bar/model.h"

#include "cad_viewer/model_interface.h"

#include <QPushButton>
#include <QVBoxLayout>

namespace cad_viewer::tool_bar {

Model::Model(ModelInterface* model_interface, QWidget* parent)
  : QWidget{parent}
  , m_model_interface{model_interface}
{
  auto* layout = new QVBoxLayout{this};
  setLayout(layout);

  auto box_btn = new QPushButton{tr("&Box"), this};
  QObject::connect(box_btn, &QPushButton::clicked, this, &Model::primitiveBox);
  layout->addWidget(box_btn);
}

void Model::primitiveBox()
{
  m_model_interface->createBox(100, 100, 100);
}

} // namespace cad_viewer::tool_bar
