#ifndef PETGUI_CONST_H
#define PETGUI_CONST_H

#include <QString>

namespace PetGUI::Const {
	
	const static QString ERROR_TITLE = "Error";
	const static QString INFO_TITLE = "Info";
	
	const static QString LOGIN_REGEX = "^[a-zA-Z0-9]([._](?![._])|[a-zA-Z0-9]){6,18}[a-zA-Z0-9]$";
	const static QString PASSWORD_REGEX = "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,10}$";
	const static QString EMAIL_REGEX = "^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$";
	
}

#endif // PETGUI_CONST_H
