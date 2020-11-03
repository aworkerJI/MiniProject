from PyQt5 import uic
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QAbstractItemView, QHeaderView, QAction, QMessageBox, QTableWidgetItem

from CoffeeApp.application_coffee_practice.dao.sale_dao import SaleDao


class SaleUI(QWidget):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("ui/sale.ui")  # 밖에 있는 main에서 실행할때
        self.ui.show()
        self.Sale = SaleDao()
        self.ui.tableWidget.setHorizontalHeaderLabels(["번호", "코드", "가격", "판매개수", "마진율"])  # 바로 넣어 주기
        # row단위 선택 / 그전에는 셀 단위로 선택 되었음
        self.ui.tableWidget.setSelectionBehavior(QAbstractItemView.SelectRows)
        # 수정 불가능
        self.ui.tableWidget.setEditTriggers(QAbstractItemView.NoEditTriggers)
        # 균일한 간격으로 재배치
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.ui.btn_search.clicked.connect(self.select_item)
        self.ui.btn_add.clicked.connect(self.add_item)
        self.ui.btn_update.clicked.connect(self.update_item)
        self.ui.btn_del.clicked.connect(self.delete_item)
        self.ui.btn_init.clicked.connect(self.init_item)
        self.ui.btn_update.hide()
        self.load_data(self.Sale.select_item())
        # 마우스 우클릭시 메뉴
        self.set_context_menu(self.ui.tableWidget)

    def init_item(self):
        self.ui.le_no.clear()
        self.ui.le_code.clear()
        self.ui.le_price.clear()
        self.ui.le_saleCnt.clear()
        self.ui.le_marginRate.clear()
        self.ui.btn_add.show()
        self.ui.btn_del.show()
        self.ui.btn_init.show()
        self.ui.btn_search.show()
        self.load_data(self.Sale.select_item())

    def __update(self):
        QMessageBox.information(self, '수정', "수정할 자료를 불러오겠습니다.", QMessageBox.Ok)
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]
        self.ui.le_no.setText(self.ui.tableWidget.item(selectionIdxs.row(), 0).text())
        self.ui.le_code.setText(self.ui.tableWidget.item(selectionIdxs.row(), 1).text())
        self.ui.le_price.setText(self.ui.tableWidget.item(selectionIdxs.row(), 2).text())
        self.ui.le_saleCnt.setText(self.ui.tableWidget.item(selectionIdxs.row(), 3).text())
        self.ui.le_marginRate.setText(self.ui.tableWidget.item(selectionIdxs.row(), 4).text())
        self.ui.btn_update.show()
        self.ui.le_no.setEnabled(False)
        self.ui.le_code.setEnabled(False)
        self.ui.btn_add.hide()
        self.ui.btn_del.hide()
        self.ui.btn_init.hide()
        self.ui.btn_search.hide()

    def __delete(self):
        QMessageBox.information(self, '삭제', "삭제 하겠습니다.", QMessageBox.Ok)
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]  # 여러개중 하나 선택하기
    def set_context_menu(self ,tv):
        tv.setContextMenuPolicy(Qt.ActionsContextMenu)  # 바로가기 메뉴를 달겠다.
        update_action = QAction("수정할 자료 불러오기", tv)
        tv.addAction(update_action)
        update_action.triggered.connect(self.__update)

    def get_item_from_le(self):
        no         = self.ui.le_no.text()
        code       = self.ui.le_code.text()
        price      = self.ui.le_price.text()
        saleCnt    = self.ui.le_saleCnt.text()
        marginRate = self.ui.le_marginRate.text()
        return self.create_item(no, code, price, saleCnt, marginRate)

    def create_item(self, no, code, price, saleCnt, marginRate):
        item_no = QTableWidgetItem()
        item_no.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_no.setData(Qt.DisplayRole, no)
        item_code = QTableWidgetItem()
        item_code.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_code.setData(Qt.DisplayRole, code)
        item_price = QTableWidgetItem()
        item_price.setTextAlignment(Qt.AlignCenter)
        item_price.setData(Qt.DisplayRole, price)
        item_saleCnt = QTableWidgetItem()
        item_saleCnt.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_saleCnt.setData(Qt.DisplayRole, saleCnt)
        item_marginRate = QTableWidgetItem()
        item_marginRate.setTextAlignment(Qt.AlignCenter)
        item_marginRate.setData(Qt.DisplayRole, marginRate)
        return item_no, item_code, item_price, item_saleCnt, item_marginRate

    def load_data(self, data):
        self.ui.tableWidget.setRowCount(0)      # 행 초기화
        for idx, (no, code, price, saleCnt, marginRate) in enumerate(data):  # enumerate 0, 1, 2 담긴다
            item_no, item_code, item_price, item_saleCnt, item_marginRate = \
            self.create_item(no, code, price, saleCnt, marginRate)
            nextIdx = self.ui.tableWidget.rowCount()
            self.ui.tableWidget.insertRow(nextIdx)
            self.ui.tableWidget.setItem(nextIdx, 0, item_no)
            self.ui.tableWidget.setItem(nextIdx, 1, item_code)
            self.ui.tableWidget.setItem(nextIdx, 2, item_price)
            self.ui.tableWidget.setItem(nextIdx, 3, item_saleCnt)
            self.ui.tableWidget.setItem(nextIdx, 4, item_marginRate)
            self.ui.le_no.setEnabled(False)
            self.ui.le_code.setEnabled(True)
            self.ui.le_price.setEnabled(True)
            self.ui.le_saleCnt.setEnabled(True)
            self.ui.le_marginRate.setEnabled(True)

    def add_item(self):
        item_no, item_code, item_price, item_saleCnt, item_marginRate = self.get_item_from_le()  # 밑에서 받아오기
        currentIdx = self.ui.tableWidget.rowCount()
        self.ui.tableWidget.insertRow(currentIdx)  # Row 추가
        self.Sale.insert_item(self.ui.le_code.text(), self.ui.le_price.text(),
                              self.ui.le_saleCnt.text(), self.ui.le_marginRate.text())
        self.init_item()
        self.load_data(self.Sale.select_item())
        QMessageBox.information(self, '추가', "추가 되었습니다.", QMessageBox.Ok)

    def update_item(self):
        item_no, item_code, item_price, item_saleCnt, item_marginRate = self.get_item_from_le()  # 밑에서 받아오기
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]
        self.Sale.update_item(self.ui.le_code.text(), self.ui.le_price.text(),
                              self.ui.le_saleCnt.text(), self.ui.le_marginRate.text(),self.ui.le_no.text())
        self.load_data(self.Sale.select_item())
        self.init_item()
        self.ui.btn_update.hide()
        QMessageBox.information(self, '수정', "수정 되었습니다.", QMessageBox.Ok)

    def delete_item(self):
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]  # 여러개중 하나 선택하기
        self.Sale.delete_item(self.ui.tableWidget.item(selectionIdxs.row(), 0).text())
        self.init_item()
        self.load_data(self.Sale.select_item())
        QMessageBox.information(self, '삭제', "삭제 되었습니다.", QMessageBox.Ok)

    def select_item(self):
        item_no, item_code, item_price, item_saleCnt, item_marginRate = self.get_item_from_le()  # 밑에서 받아오기
        currentIdx = self.ui.tableWidget.rowCount()
        print(self.ui.le_no.text())
        self.load_data(self.Sale.select_item(self.ui.le_code.text()))







