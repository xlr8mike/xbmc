#pragma once
/*
 *      Copyright (C) 2013 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <vector>

#include "SettingVisibility.h"

#define XML_SETTING     "setting"

#define XML_ATTR_ID     "id"
#define XML_ATTR_LABEL  "label"
#define XML_ATTR_HELP   "help"
#define XML_ATTR_TYPE   "type"

class CSettingsManager;
class TiXmlNode;

/*!
 \ingroup settings
 \brief Interface defining the base of all setting objects
 */
class ISetting
{
public:
  /*!
   \brief Creates a new setting object with the given identifier.

   \param id Identifier of the setting object
   \param settingsManager Reference to the settings manager
   */
  ISetting(const std::string &id, CSettingsManager *settingsManager = NULL);
  virtual ~ISetting() { }

  /*!
   \brief Deserializes the given XML node into the properties of the setting
   object.

   If the update parameter is true, the checks for mandatory properties are
   skipped and values are only updated.

   \param node XML node containing the properties of the setting object
   \param update Whether to perform checks for mandatory properties or not
   \return True if deserialization was successful, false otherwise
   */
  virtual bool Deserialize(const TiXmlNode *node, bool update = false);

  /*!
   \brief Gets the identifier of the setting object.

   \return Identifier of the setting object
   */
  const std::string& GetId() const { return m_id; }
  /*!
   \brief Whether the setting object is visible or hidden.

   \return True if the setting object is visible, false otherwise
   */
  bool IsVisible() const { return m_visible; }
  /*!
   \brief Updates the visibility state of the setting object.
   */
  void CheckVisible();
  /*!
   \brief Sets the visibility state of the setting object.

   \param visible Whether the setting object shall be visible or not
   */
  void SetVisible(bool visible) { m_visible = visible; }

  /*!
   \brief Deserializes the given XML node to retrieve a setting object's
   identifier.

   \param node XML node containing a setting object's identifier
   \param identification Will contain the deserialized setting object's identifier
   \return True if a setting object's identifier was deserialized, false otherwise
   */
  static bool DeserializeIdentification(const TiXmlNode *node, std::string &identification);

protected:
  std::string m_id;
  CSettingsManager *m_settingsManager;

private:
  bool m_visible;
  CSettingVisibility m_visibilityCondition;
};
