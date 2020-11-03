from PyQt5 import uic
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QAbstractItemView, QHeaderView, QTableWidgetItem

from CoffeeApp.application_coffee_practice.dao.sale_detail_dao import SaleDetailDao


class SaledetailUI(QWidget):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("ui/saledetail.ui")  # 밖에 있는 main에서 실행할때
        self.ui.show()
        self.saledetail = SaleDetailDao()   # 클래스 SaleDetailDao()를 SaledetailUI에서 객체 속성 초기
        # 균일한 간격으로 재배치
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.load_data(self.saledetail.select_item())
        self.ui.btn_sale.clicked.connect(self.orderby_default)
        self.ui.btn_saleprice_asc.clicked.connect(self.orderby_saleprice_asc)
        self.ui.btn_saleprice_desc.clicked.connect(self.orderby_saleprice_desc)
        self.ui.btn_marginprice_asc.clicked.connect(self.orderby_marginprice_asc)
        self.ui.btn_marginprice_desc.clicked.connect(self.orderby_marginprice_desc)

    def load_data(self, data=None):                     # saledetail default 값
        self.ui.tableWidget.setRowCount(0)              # tableWidget 초기화
        self.ui.tableWidget.setColumnCount(5)           # tableWidget Column수 설정
        self.ui.tableWidget.setHorizontalHeaderLabels(["번호", "판매가격", "세금", "공급가격", "마진가"])
        for idx, (no, sale_price, addTax, supply_price, marginPrice) in enumerate(data):
            item_no, item_sale_price, item_addTax, item_supply_price, item_marginPrice \
            = self.create_item(no, sale_price, addTax, supply_price, marginPrice)
            nextIdx = self.ui.tableWidget.rowCount()
            self.ui.tableWidget.insertRow(nextIdx)
            self.ui.tableWidget.setItem(nextIdx, 0, item_no)
            self.ui.tableWidget.setItem(nextIdx, 1, item_sale_price)
            self.ui.tableWidget.setItem(nextIdx, 2, item_addTax)
            self.ui.tableWidget.setItem(nextIdx, 3, item_supply_price)
            self.ui.tableWidget.setItem(nextIdx, 4, item_marginPrice)

    def create_item(self, no, sale_price, addTax, supply_price, marginPrice): # saledetail default 값
        item_no = QTableWidgetItem()
        item_no.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_no.setData(Qt.DisplayRole, no)
        item_sale_price = QTableWidgetItem()
        item_sale_price.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_sale_price.setData(Qt.DisplayRole, format(sale_price, ',d'))
        item_addTax = QTableWidgetItem()
        item_addTax.setTextAlignment(Qt.AlignCenter)
        item_addTax.setData(Qt.DisplayRole, format(addTax, ',d'))
        item_supply_price = QTableWidgetItem()
        item_supply_price.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_supply_price.setData(Qt.DisplayRole, format(supply_price, ',d'))
        item_marginPrice = QTableWidgetItem()
        item_marginPrice.setTextAlignment(Qt.AlignCenter)
        item_marginPrice.setData(Qt.DisplayRole, format(marginPrice, ',d'))
        return item_no, item_sale_price, item_addTax, item_supply_price, item_marginPrice

    def load_data_orderby(self, data=None):                     # saledetail default 값
        self.ui.tableWidget.setRowCount(0)              # tableWidget 초기화
        self.ui.tableWidget.setColumnCount(10)           # tableWidget Column수 설정
        self.ui.tableWidget.setHorizontalHeaderLabels(["순위", "코드", "이름", "가격", "판매개수", "공급가격",
                                                       "부가세", "판매가격", "마진율", "마진가격"])
        for idx, (rank, code, name, price, salecnt, supply_price, addTax, sale_price, marginRate, marginPrice) in enumerate(data):
            item_rank, item_code, item_name, item_price, item_salecnt, item_supply_price, item_addTax, item_sale_price, item_marginRate, item_marginPrice \
            = self.create_item_orderby(rank, code, name, price, salecnt, supply_price, addTax, sale_price, marginRate, marginPrice)
            nextIdx = self.ui.tableWidget.rowCount()
            self.ui.tableWidget.insertRow(nextIdx)
            self.ui.tableWidget.setItem(nextIdx, 0, item_rank)
            self.ui.tableWidget.setItem(nextIdx, 1, item_code)
            self.ui.tableWidget.setItem(nextIdx, 2, item_name)
            self.ui.tableWidget.setItem(nextIdx, 3, item_price)
            self.ui.tableWidget.setItem(nextIdx, 4, item_salecnt)
            self.ui.tableWidget.setItem(nextIdx, 5, item_supply_price)
            self.ui.tableWidget.setItem(nextIdx, 6, item_addTax)
            self.ui.tableWidget.setItem(nextIdx, 7, item_sale_price)
            self.ui.tableWidget.setItem(nextIdx, 8, item_marginRate)
            self.ui.tableWidget.setItem(nextIdx, 9, item_marginPrice)

    def create_item_orderby(self, rank, code, name, price, salecnt, supply_price, addTax, sale_price, marginRate, marginPrice): # saledetail default 값
        item_rank = QTableWidgetItem()
        item_rank.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_rank.setData(Qt.DisplayRole, rank)
        item_code = QTableWidgetItem()
        item_code.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_code.setData(Qt.DisplayRole, code)
        item_name = QTableWidgetItem()
        item_name.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_name.setData(Qt.DisplayRole, name)
        item_price = QTableWidgetItem()
        item_price.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_price.setData(Qt.DisplayRole, format(price, ',d'))
        item_salecnt = QTableWidgetItem()
        item_salecnt.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_salecnt.setData(Qt.DisplayRole, salecnt)
        item_supply_price = QTableWidgetItem()
        item_supply_price.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_supply_price.setData(Qt.DisplayRole, format(supply_price, ',d'))
        item_addTax = QTableWidgetItem()
        item_addTax.setTextAlignment(Qt.AlignCenter)
        item_addTax.setData(Qt.DisplayRole, format(addTax, ',d'))
        item_sale_price = QTableWidgetItem()
        item_sale_price.setTextAlignment(Qt.AlignCenter)  # Qt Core
        item_sale_price.setData(Qt.DisplayRole, format(sale_price, ',d'))
        item_marginRate = QTableWidgetItem()
        item_marginRate.setTextAlignment(Qt.AlignCenter)
        item_marginRate.setData(Qt.DisplayRole, str(marginRate)+'%')
        item_marginPrice = QTableWidgetItem()
        item_marginPrice.setTextAlignment(Qt.AlignCenter)
        item_marginPrice.setData(Qt.DisplayRole, format(marginPrice, ',d'))
        return item_rank, item_code, item_name, item_price, item_salecnt, item_supply_price, item_addTax, item_sale_price, item_marginRate, item_marginPrice

    def orderby_default(self):
        self.load_data(self.saledetail.select_item())

    def orderby_saleprice_asc(self):
        self.load_data_orderby(self.saledetail.orderby_saleprice_asc())

    def orderby_saleprice_desc(self):
        self.load_data_orderby(self.saledetail.orderby_saleprice_desc())

    def orderby_marginprice_asc(self):
        self.load_data_orderby(self.saledetail.orderby_marginprice_asc())

    def orderby_marginprice_desc(self):
        self.load_data_orderby(self.saledetail.orderby_marginprice_desc())




