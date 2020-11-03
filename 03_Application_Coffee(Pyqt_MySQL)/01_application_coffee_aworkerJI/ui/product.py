from PyQt5 import uic
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QAbstractItemView, QHeaderView, QTableWidgetItem, QAction, QMessageBox

from CoffeeApp.application_coffee_practice.dao.product_dao import ProductDao
from CoffeeApp.application_coffee_practice.ui.sale import SaleUI
from CoffeeApp.application_coffee_practice.ui.saledetail import SaledetailUI


class ProductUI(QWidget):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("ui/product.ui")  # 밖에 있는 main에서 실행할때
        self.ui.show()
        self.Product = ProductDao()
        self.ui.tableWidget.setHorizontalHeaderLabels(["코드", "제품"])  # 바로 넣어 주기
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
        self.ui.btn_sale.clicked.connect(self.show_sale)             # 가격조정show
        self.ui.btn_saledetail.clicked.connect(self.show_saledetail) # 판매세부내역show
        self.ui.btn_update.hide()
        self.load_data(self.Product.select_item())
        # 마우스 우클릭시 메뉴
        self.set_context_menu(self.ui.tableWidget)

    def init_item(self):
        self.ui.le_code.clear()
        self.ui.le_name.clear()
        self.ui.btn_add.show()
        self.ui.btn_del.show()
        self.ui.btn_init.show()
        self.ui.btn_search.show()
        self.ui.le_code.setEnabled(True)
        self.ui.le_name.setEnabled(True)
        self.load_data(self.Product.select_item())

    def show_sale(self):
        self.show_sale = SaleUI()         # 창은 생성해두

    def show_saledetail(self):
        self.show_saledetail = SaledetailUI()

    def __update(self):
        QMessageBox.information(self, '수정', "수정할 자료를 불러오겠습니다.", QMessageBox.Ok)
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]
        self.ui.le_code.setText(self.ui.tableWidget.item(selectionIdxs.row(), 0).text())
        self.ui.le_name.setText(self.ui.tableWidget.item(selectionIdxs.row(), 1).text())
        self.ui.btn_update.show()
        self.ui.le_code.setEnabled(False)
        # self.ui.le_name.setEnabled(True)
        self.ui.btn_add.hide()
        self.ui.btn_del.hide()
        self.ui.btn_init.hide()
        self.ui.btn_search.hide()

    def __delete(self):
        QMessageBox.information(self, '삭제', "삭제 하겠습니다.", QMessageBox.Ok)
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]  # 여러개중 하나 선택하기

    def set_context_menu(self,tv):
        tv.setContextMenuPolicy(Qt.ActionsContextMenu)  # 바로가기 메뉴를 달겠다.
        update_action = QAction("수정할 자료 불러오기", tv)
        tv.addAction(update_action)     # 마우스 우 클릭시 Qaction실행
        update_action.triggered.connect(self.__update)

    def get_item_from_le(self):
        code = self.ui.le_code.text()
        name = self.ui.le_name.text()
        return self.create_item(code, name)

    def create_item(self, code, name):
        item_code = QTableWidgetItem()
        item_code.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_code.setData(Qt.DisplayRole, code)
        item_name = QTableWidgetItem()
        item_name.setTextAlignment(Qt.AlignCenter)
        item_name.setData(Qt.DisplayRole, name)
        return item_code, item_name

    def load_data(self, data):
        self.ui.tableWidget.setRowCount(0)  # 행 초기화
        for idx, (code, name) in enumerate(data):  # enumerate 0, 1, 2 담긴다
            item_code, item_name = self.create_item(code, name)
            nextIdx = self.ui.tableWidget.rowCount()
            self.ui.tableWidget.insertRow(nextIdx)
            self.ui.tableWidget.setItem(nextIdx, 0, item_code)
            self.ui.tableWidget.setItem(nextIdx, 1, item_name)

    def add_item(self):
        item_code, item_name = self.get_item_from_le()  # 밑에서 받아오기
        currentIdx = self.ui.tableWidget.rowCount()
        self.ui.tableWidget.insertRow(currentIdx)  # Row 추가
        self.Product.insert_item(self.ui.le_code.text(), self.ui.le_name.text())
        self.init_item()
        self.load_data(self.Product.select_item())
        QMessageBox.information(self, '추가', "추가 되었습니다.", QMessageBox.Ok)

    def update_item(self):
        item_code, item_name = self.get_item_from_le()  # 밑에서 받아오기
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]
        self.Product.update_item(self.ui.le_name.text(), self.ui.le_code.text() )
        self.load_data(self.Product.select_item())
        self.init_item()
        self.ui.btn_update.hide()
        QMessageBox.information(self, '수정', "수정 되었습니다.", QMessageBox.Ok)

    def delete_item(self):
        selectionIdxs = self.ui.tableWidget.selectedIndexes()[0]  # 여러개중 하나 선택하기
        self.Product.delete_item(self.ui.tableWidget.item(selectionIdxs.row(), 0).text())
        self.init_item()
        self.load_data(self.Product.select_item())
        QMessageBox.information(self, '삭제', "삭제 되었습니다.", QMessageBox.Ok)

    def select_item(self):
        item_code, item_name = self.get_item_from_le()  # 밑에서 받아오기
        currentIdx = self.ui.tableWidget.rowCount()
        self.load_data(self.Product.select_item(self.ui.le_code.text()))



