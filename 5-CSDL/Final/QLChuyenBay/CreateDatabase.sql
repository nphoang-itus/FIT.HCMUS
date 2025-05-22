-- Tạo cơ sở dữ liệu
CREATE DATABASE QuanLyChuyenBay;
GO

USE QuanLyChuyenBay;
GO

-- Tạo bảng KHACHHANG
CREATE TABLE KHACHHANG (
    MAKH NVARCHAR(15) PRIMARY KEY,
    TEN NVARCHAR(15),
    DCHI NVARCHAR(50),
    DTHOAI NVARCHAR(12)
);

-- Tạo bảng NHANVIEN
CREATE TABLE NHANVIEN (
    MANV NVARCHAR(15) PRIMARY KEY,
    TEN NVARCHAR(15),
    DCHI NVARCHAR(50),
    DTHOAI NVARCHAR(12),
    LUONG DECIMAL(10,2),
    LOAINV BIT -- 1=phi công, 0=tiếp viên
);

-- Tạo bảng LOAIMB (Loại máy bay)
CREATE TABLE LOAIMB (
    MALOAI NVARCHAR(15) PRIMARY KEY,
    HANGSX NVARCHAR(15)
);

-- Tạo bảng MAYBAY
CREATE TABLE MAYBAY (
    SOHIEU INT,
    MALOAI NVARCHAR(15),
    PRIMARY KEY (SOHIEU, MALOAI),
    FOREIGN KEY (MALOAI) REFERENCES LOAIMB(MALOAI)
);

-- Tạo bảng CHUYENBAY
CREATE TABLE CHUYENBAY (
    MACB NVARCHAR(4) PRIMARY KEY,
    SBDI NVARCHAR(3),
    SBDEN NVARCHAR(3),
    GIODI TIME,
    GIODEN TIME
);

-- Tạo bảng LICHBAY
CREATE TABLE LICHBAY (
    NGAYDI DATE,
    MACB NVARCHAR(4),
    SOHIEU INT,
    MALOAI NVARCHAR(15),
    PRIMARY KEY (NGAYDI, MACB),
    FOREIGN KEY (MACB) REFERENCES CHUYENBAY(MACB),
    FOREIGN KEY (SOHIEU, MALOAI) REFERENCES MAYBAY(SOHIEU, MALOAI)
);

-- Tạo bảng DATCHO
CREATE TABLE DATCHO (
    MAKH NVARCHAR(15),
    NGAYDI DATE,
    MACB NVARCHAR(4),
    PRIMARY KEY (MAKH, NGAYDI, MACB),
    FOREIGN KEY (MAKH) REFERENCES KHACHHANG(MAKH),
    FOREIGN KEY (NGAYDI, MACB) REFERENCES LICHBAY(NGAYDI, MACB)
);

-- Tạo bảng KHANANG
CREATE TABLE KHANANG (
    MANV NVARCHAR(15),
    MALOAI NVARCHAR(15),
    PRIMARY KEY (MANV, MALOAI),
    FOREIGN KEY (MANV) REFERENCES NHANVIEN(MANV),
    FOREIGN KEY (MALOAI) REFERENCES LOAIMB(MALOAI)
);

-- Tạo bảng PHANCONG
CREATE TABLE PHANCONG (
    MANV NVARCHAR(15),
    NGAYDI DATE,
    MACB NVARCHAR(4),
    PRIMARY KEY (MANV, NGAYDI, MACB),
    FOREIGN KEY (MANV) REFERENCES NHANVIEN(MANV),
    FOREIGN KEY (NGAYDI, MACB) REFERENCES LICHBAY(NGAYDI, MACB)
);

-- Thêm dữ liệu vào bảng NHANVIEN
INSERT INTO NHANVIEN (MANV, TEN, DCHI, DTHOAI, LUONG, LOAINV) VALUES
('1006', N'Chi', N'12/6 Nguyen Kiem', '8120012', 150000, 0),
('1005', N'Giao', N'65 Nguyen Thai Son', '8324467', 500000, 0),
('1001', N'Huong', N'8 Dien Bien Phu', '8330733', 500000, 1),
('1002', N'Phong', N'1 Ly Thuong Kiet', '8308117', 450000, 1),
('1004', N'Phuong', N'351 Lac Long Quan', '8308155', 250000, 0),
('1003', N'Quang', N'78 Truong Dinh', '8324461', 350000, 1),
('1007', N'Tam', N'36 Nguyen Van Cu', '8458188', 500000, 0);

-- Thêm dữ liệu vào bảng KHACHHANG
INSERT INTO KHACHHANG (MAKH, TEN, DCHI, DTHOAI) VALUES
('0009', N'Nga', N'223 Nguyen Trai', '8932320'),
('0101', N'Anh', N'567 Tran Phu', '8826729'),
('0045', N'Thu', N'285 Le Loi', '8932203'),
('0012', N'Ha', N'435 Quang Trung', '8933232'),
('0238', N'Hung', N'456 Pasteur', '9812101'),
('0397', N'Thanh', N'234 Le Van Si', '8952943'),
('0582', N'Mai', N'789 Nguyen Du', NULL),
('0934', N'Minh', N'678 Le Lai', NULL),
('0091', N'Hai', N'345 Hung Vuong', '8893223'),
('0314', N'Phuong', N'395 Vo Van Tan', '8232320'),
('0613', N'Vu', N'348 CMT8', '8343232'),
('0586', N'Son', N'123 Bach Dang', '8556223'),
('0422', N'Tien', N'75 Nguyen Thong', '8332222');


INSERT INTO LOAIMB (MALOAI, HANGSX) VALUES
('A310', 'Airbus'),
('A320', 'Airbus'),
('A330', 'Airbus'),
('A340', 'Airbus'),
('B727', 'Boeing'),
('B747', 'Boeing'),
('B757', 'Boeing'),
('DC10', 'MD'),
('DC9', 'MD');

-- Thêm dữ liệu vào bảng MAYBAY
INSERT INTO MAYBAY (SOHIEU, MALOAI) VALUES
(10, 'B747'),
(11, 'B727'),
(13, 'B727'),
(13, 'B747'),
(21, 'DC10'),
(21, 'DC9'),
(22, 'B757'),
(22, 'DC9'),
(23, 'DC9'),
(24, 'DC9'),
(70, 'A310'),
(80, 'A310'),
(93, 'B757');

-- Thêm dữ liệu vào bảng CHUYENBAY
INSERT INTO CHUYENBAY (MACB, SBDI, SBDEN, GIODI, GIODEN) VALUES
('100', 'SLC', 'BOS', '08:00', '17:50'),
('112', 'DCA', 'DEN', '14:00', '18:07'),
('121', 'STL', 'SLC', '07:00', '09:13'),
('122', 'STL', 'YYV', '08:30', '10:19'),
('206', 'DFW', 'STL', '09:00', '11:40'),
('330', 'JFK', 'YYV', '16:00', '18:53'),
('334', 'ORD', 'MIA', '12:00', '14:14'),
('335', 'MIA', 'ORD', '15:00', '17:14'),
('336', 'ORD', 'MIA', '18:00', '20:14'),
('337', 'MIA', 'ORD', '20:30', '23:53'),
('394', 'DFW', 'MIA', '19:00', '21:30'),
('395', 'MIA', 'DFW', '21:00', '23:43'),
('449', 'CDG', 'DEN', '10:00', '19:29'),
('930', 'YYV', 'DCA', '13:00', '16:10'),
('931', 'DCA', 'YYV', '17:00', '18:10'),
('932', 'DCA', 'YYV', '18:00', '19:10'),
('991', 'BOS', 'ORD', '17:00', '18:22');

-- Thêm dữ liệu vào bảng KHANANG
INSERT INTO KHANANG (MANV, MALOAI) VALUES
('1001', 'B727'),
('1001', 'B747'),
('1001', 'DC10'),
('1001', 'DC9'),
('1002', 'A320'),
('1002', 'A340'),
('1002', 'B757'),
('1002', 'DC9'),
('1003', 'A310'),
('1003', 'DC9');

-- Thêm dữ liệu vào bảng LICHBAY
INSERT INTO LICHBAY (NGAYDI, MACB, SOHIEU, MALOAI) VALUES
('2000-11-01', '100', 80, 'A310'),
('2000-11-01', '112', 21, 'DC10'),
('2000-11-01', '206', 22, 'DC9'),
('2000-11-01', '334', 10, 'B747'),
('2000-11-01', '395', 23, 'DC9'),
('2000-11-01', '991', 22, 'B757'),
('2000-11-01', '337', 10, 'B747'),
('2000-10-31', '100', 11, 'B727'),
('2000-10-31', '112', 11, 'B727'),
('2000-10-31', '206', 13, 'B727'),
('2000-10-31', '334', 10, 'B747'),
('2000-10-31', '335', 10, 'B747'),
('2000-10-31', '337', 24, 'DC9'),
('2000-10-31', '449', 70, 'A310');

-- Thêm dữ liệu vào bảng DATCHO
INSERT INTO DATCHO (MAKH, NGAYDI, MACB) VALUES
('0009', '2000-11-01', '100'),
('0009', '2000-10-31', '449'),
('0045', '2000-11-01', '991'),
('0012', '2000-10-31', '206'),
('0238', '2000-10-31', '334'),
('0582', '2000-11-01', '991'),
('0091', '2000-11-01', '100'),
('0314', '2000-10-31', '449'),
('0613', '2000-11-01', '100'),
('0586', '2000-11-01', '991'),
('0586', '2000-10-31', '100'),
('0422', '2000-10-31', '449');

-- Thêm dữ liệu vào bảng PHANCONG
INSERT INTO PHANCONG (MANV, NGAYDI, MACB) VALUES
('1001', '2000-11-01', '100'),
('1001', '2000-10-31', '100'),
('1002', '2000-11-01', '100'),
('1002', '2000-10-31', '100'),
('1003', '2000-10-31', '100'),
('1003', '2000-10-31', '337'),
('1004', '2000-10-31', '100'),
('1004', '2000-10-31', '337'),
('1005', '2000-10-31', '337'),
('1006', '2000-11-01', '991'),
('1006', '2000-10-31', '337'),
('1007', '2000-11-01', '112'),
('1007', '2000-11-01', '991'),
('1007', '2000-10-31', '206');

-- Kiểm tra dữ liệu trong bảng NHANVIEN
SELECT * FROM NHANVIEN;

-- Kiểm tra dữ liệu trong bảng KHACHHANG
SELECT * FROM KHACHHANG;

-- Kiểm tra dữ liệu trong bảng LOAIMB
SELECT * FROM LOAIMB;

-- Kiểm tra dữ liệu trong bảng MAYBAY
SELECT * FROM MAYBAY;

-- Kiểm tra dữ liệu trong bảng CHUYENBAY
SELECT * FROM CHUYENBAY;

-- Kiểm tra dữ liệu trong bảng LICHBAY
SELECT * FROM LICHBAY;

-- Kiểm tra dữ liệu trong bảng DATCHO
SELECT * FROM DATCHO;

-- Kiểm tra dữ liệu trong bảng KHANANG
SELECT * FROM KHANANG;

-- Kiểm tra dữ liệu trong bảng PHANCONG
SELECT * FROM PHANCONG;

-- Cho biết mã số, tên phi công, địa chỉ, điện thoại của các phi công đã từng lái máy bay loại B747.
SELECT NV.MANV, NV.TEN, NV.DCHI, NV.DTHOAI
FROM NHANVIEN NV
    JOIN PHANCONG PC ON PC.MANV = NV.MANV
    JOIN LICHBAY LB ON LB.MACB = PC.MACB
WHERE LB.MALOAI = 'B747' AND NV.LOAINV = 1;

-- 2. Cho biết mã số và ngày đi của các chuyến bay xuất phát từ sân bay DCA trong khoảng thời gian từ 14 giờ đến 18 giờ.
SELECT LB.MACB, LB.NGAYDI
FROM LICHBAY LB
    JOIN CHUYENBAY CB ON CB.MACB = LB.MACB
WHERE CB.SBDI = 'DCA' AND CB.GIODI BETWEEN '14:00' AND '18:00';

-- 3. Cho biết tên những nhân viên được phân công trên chuyến bay có mã số 100 xuất phát tại sân bay SLC. Các dòng dữ liệu xuất ra không được phép trùng lắp.
SELECT DISTINCT NV.TEN
FROM NHANVIEN NV
    JOIN PHANCONG PC ON PC.MANV = NV.MANV
    JOIN CHUYENBAY CB ON CB.MACB = PC.MACB
WHERE CB.MACB = '100' AND SBDI = 'SLC';


-- 4. Cho biết mã loại và số hiệu máy bay đã từng xuất phát tại sân bay MIA. Các dòng dữ liệu xuất ra không được phép trùng lắp.
SELECT DISTINCT LB.MALOAI, LB.SOHIEU
FROM LICHBAY LB
    JOIN CHUYENBAY CB ON LB.MACB = CB.MACB
WHERE SBDI = 'MIA';

-- 5. Cho biết mã chuyến bay, ngày đi, cùng với tên, địa chỉ, điện thoại của tất cả các hành khách đi trên chuyến bay đó. Sắp xếp theo thứ tự tăng dần của mã chuyến bay và theo ngày đi giảm dần.
SELECT DC.MACB, DC.NGAYDI, KH.TEN, KH.DCHI, KH.DTHOAi
FROM KHACHHANG KH
    JOIN DATCHO DC ON KH.MAKH = DC.MAKH
ORDER BY DC.MACB ASC, DC.NGAYDI DESC

-- 6. Cho biết mã chuyến bay, ngày đi, cùng với tên, địa chỉ, điện thoại của tất cả những nhân viên được phân công trong chuyến bay đó. Sắp xếp theo thứ tự tăng dần của mã chuyến bay và theo ngày đi giảm dần.
SELECT PC.MACB, PC.NGAYDI, NV.TEN, NV.DCHI, NV.DTHOAI
FROM NHANVIEN NV
    JOIN PHANCONG PC ON NV.MANV = PC.MANV
ORDER BY PC.MACB ASC, PC.NGAYDI DESC

-- 7. Cho biết mã chuyến bay, ngày đi, mã số và tên của những phi công được phân công vào chuyến bay hạ cánh xuống sân bay ORD.
SELECT PC.MACB, PC.NGAYDI, NV.MANV, NV.MANV, NV.TEN
FROM PHANCONG PC
    JOIN NHANVIEN NV ON PC.MANV = NV.MANV
    JOIN CHUYENBAY CB ON CB.MACB = PC.MACB
WHERE NV.LOAINV = '1' AND CB.SBDEN = 'ORD'

-- 8. Cho biết các chuyến bay (mã số chuyến bay, ngày đi và tên của phi công) trong đó phi công có mã 1001 được phân công lái.
SELECT DISTINCT PC.MACB, PC.NGAYDI, NV.MANV, NV.TEN
FROM PHANCONG PC
    JOIN NHANVIEN NV ON NV.MANV = PC.MANV
WHERE NV.LOAINV = 1 AND NV.MANV = '1001'

-- Cho biết thông tin (mã chuyến bay, sân bay đi, giờ đi, giờ đến, ngày đi) của những chuyến bay hạ cánh xuống DEN. Các chuyến bay được liệt kê theo ngày đi giảm dần và sân bay xuất phát (SBDI) tăng dần .
SELECT CB.MACB, CB.SBDI, CB.GIODI, CB.GIODEN, LB.NGAYDI
FROM CHUYENBAY CB
    JOIN LICHBAY LB ON CB.MACB = LB.MACB
WHERE SBDEN = 'DEN'
ORDER BY LB.NGAYDI DESC, CB.SBDI ASC;

-- Với mỗi phi công, cho biết hãng sản xuất và mã loại máy bay mà phi công này có khả năng bay được. Xuất ra tên phi công, hãng sản xuất và mã loại máy bay.
SELECT DISTINCT NV.TEN, LMB.HANGSX, LMB.MALOAI
FROM NHANVIEN NV
    JOIN KHANANG KN ON KN.MANV = NV.MANV
    JOIN LOAIMB LMB ON LMB.MALOAI = KN.MALOAI

-- Cho biết mã phi công, tên phi công đã lái máy bay trong chuyến bay mã số 100 vào ngày 11/01/2000.
SELECT NV.MANV, NV.TEN
FROM PHANCONG PC
    JOIN NHANVIEN NV ON NV.MANV = PC.MANV
WHERE NV.LOAINV = '1' AND PC.MACB = '100' AND PC.NGAYDI = '2000/11/01'

-- Cho biết mã chuyến bay, mã nhân viên, tên nhân viên được phân công vào chuyến bay xuất phát ngày 10/31/2000 tại sân bay MIA vào lúc 20:30
SELECT PC.MACB, NV.MANV, NV.TEN
FROM PHANCONG PC
    JOIN NHANVIEN NV ON NV.MANV = PC.MANV
    JOIN CHUYENBAY CB ON CB.MACB = PC.MACB
WHERE PC.NGAYDI = '2000/10/31' AND CB.SBDI = 'MIA' AND CB.GIODI = '20:30';

-- Cho biết thông tin về chuyến bay (mã chuyến bay, số hiệu, mã loại, hãng sản xuất) mà phi công "Quang" đã lái.
SELECT 

-- Cho biết tên của những phi công chưa được phân công lái chuyến bay nào.


-- Cho biết tên khách hàng đã đi chuyến bay trên máy bay của hãng "Boeing"


-- Cho biết mã các chuyến bay chỉ bay với máy bay số hiệu 10 và mã loại B747.

