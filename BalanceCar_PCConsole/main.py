from MainWidSetup import MainWidSetup
import sys
from PyQt5 import QtWidgets

app=QtWidgets.QApplication(sys.argv)
ui = MainWidSetup()    
ui.show()
sys.exit(app.exec_())
