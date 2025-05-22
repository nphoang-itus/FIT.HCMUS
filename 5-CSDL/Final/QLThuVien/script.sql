CREATE DATABASE QLTHUVIEN
GO

USE QLTHUVIEN
GO

CREATE TABLE TuaSach (
  ma_tuasach INT PRIMARY KEY,
  TuaSach NVARCHAR(255) NOT NULL,
  tacgia NVARCHAR(255),
  tomtat NVARCHAR(1000)
);

-- Create DauSach table (Book Categories)
CREATE TABLE DauSach (
  isbn INT PRIMARY KEY,
  ma_tuasach INT NOT NULL,
  ngonngu NVARCHAR(50) NOT NULL,
  bia NVARCHAR(50) DEFAULT N'Bìa cứng',
  trangthai CHAR(1) DEFAULT 'Y',
  CONSTRAINT FK_DauSach_TuaSach FOREIGN KEY (ma_tuasach) REFERENCES TuaSach(ma_tuasach)
);

-- Create CuonSach table (Book Copies)
CREATE TABLE CuonSach (
  isbn INT NOT NULL,
  Ma_CuonSach INT NOT NULL,
  TinhTrang CHAR(1) DEFAULT 'N',
  CONSTRAINT PK_CuonSach PRIMARY KEY (isbn, Ma_CuonSach),
  CONSTRAINT FK_CuonSach_DauSach FOREIGN KEY (isbn) REFERENCES DauSach(isbn)
);

-- Create DocGia table (Readers)
CREATE TABLE DocGia (
  ma_docgia INT PRIMARY KEY,
  ho NVARCHAR(50) NOT NULL,
  tenlot NCHAR(1),
  ten NVARCHAR(50) NOT NULL,
  NgaySinh DATE
);

-- Create NguoiLon table (Adult Patrons)
CREATE TABLE NguoiLon (
  ma_docgia INT PRIMARY KEY,
  sonha NVARCHAR(20),
  duong NVARCHAR(100),
  quan NVARCHAR(50),
  dienthoai NVARCHAR(15),
  han_sd DATE,
  CONSTRAINT FK_NguoiLon_DocGia FOREIGN KEY (ma_docgia) REFERENCES DocGia(ma_docgia)
);

-- Create TreEm table (Children)
CREATE TABLE TreEm (
  ma_docgia INT NOT NULL,
  ma_docgia_nguoilon INT NOT NULL,
  CONSTRAINT PK_TreEm PRIMARY KEY (ma_docgia),
  CONSTRAINT FK_TreEm_DocGia FOREIGN KEY (ma_docgia) REFERENCES DocGia(ma_docgia),
  CONSTRAINT FK_TreEm_NguoiLon FOREIGN KEY (ma_docgia_nguoilon) REFERENCES NguoiLon(ma_docgia)
);

-- Create DangKy table (Registration)
CREATE TABLE DangKy (
  isbn INT NOT NULL,
  ma_docgia INT NOT NULL,
  ngaygio_dk DATETIME NOT NULL,
  ghichu NVARCHAR(255),
  CONSTRAINT PK_DangKy PRIMARY KEY (isbn, ma_docgia, ngaygio_dk),
  CONSTRAINT FK_DangKy_DauSach FOREIGN KEY (isbn) REFERENCES DauSach(isbn),
  CONSTRAINT FK_DangKy_DocGia FOREIGN KEY (ma_docgia) REFERENCES DocGia(ma_docgia)
);

-- Create Muon table (Borrowing)
CREATE TABLE Muon (
  isbn INT NOT NULL,
  ma_cuonsach INT NOT NULL,
  ma_docgia INT NOT NULL,
  ngayGio_muon DATETIME NOT NULL,
  ngay_hethan DATETIME,
  CONSTRAINT PK_Muon PRIMARY KEY (isbn, ma_cuonsach, ma_docgia, ngayGio_muon),
  CONSTRAINT FK_Muon_CuonSach FOREIGN KEY (isbn, ma_cuonsach) REFERENCES CuonSach(isbn, Ma_CuonSach),
  CONSTRAINT FK_Muon_DocGia FOREIGN KEY (ma_docgia) REFERENCES DocGia(ma_docgia)
);

-- Create QuaTrinhMuon table (Borrowing Process)
CREATE TABLE QuaTrinhMuon (
  isbn INT NOT NULL,
  ma_cuonsach INT NOT NULL,
  ngayGio_muon DATETIME NOT NULL,
  ma_docgia INT NOT NULL,
  ngay_hethan DATETIME,
  ngayGio_tra DATETIME,
  tien_muon MONEY,
  tien_datra MONEY,
  tien_datcoc MONEY,
  ghichu NVARCHAR(255),
  CONSTRAINT PK_QuaTrinhMuon PRIMARY KEY (isbn, ma_cuonsach, ngayGio_muon, ma_docgia),
  CONSTRAINT FK_QuaTrinhMuon_Muon FOREIGN KEY (isbn, ma_cuonsach, ma_docgia, ngayGio_muon) 
    REFERENCES Muon(isbn, ma_cuonsach, ma_docgia, ngayGio_muon)
);

-- Insert sample data into TuaSach
INSERT INTO TuaSach (ma_tuasach, TuaSach, tacgia, tomtat) VALUES
(1, N'Last of the Mohicans', N'James Fenimore Cooper', N'Tóm tắt...'),
(2, N'The Night-Born', N'Jack London', N'Tóm tắt...'),
(3, N'Lemon', N'Motojirou', N'Tóm tắt...'),
(4, N'Walking', N'Henry David Thoreau', N'Tóm tắt...'),
(5, N'Ăn mày dĩ vãng', N'Chu Lai', N'Tóm tắt...'),
(6, N'Đất rừng Phương Nam', N'Đoàn Giỏi', N'Tóm tắt...'),
(7, N'Nơi bắt hành trình yêu', N'Hoàng Lai Giang', N'Tóm tắt...'),
(8, N'Cơn giông', N'Lê Văn Thảo', N'Tóm tắt...'),
(9, N'Đen vỏ, đỏ lòng', N'Mai Thanh Hải', N'Tóm tắt...'),
(10, N'Thuyền về bến ngủ', N'Mong Bình Sơn', N'Tóm tắt...'),
(11, N'Cánh tù Bạc Liêu', N'Nguyễn Hưng', N'Tóm tắt...'),
(12, N'The Village Watch-Tower', N'Kate Douglas Wiggin', N'Tóm tắt...'),
(13, N'Trả giá', N'Triệu Xuân', N'Tóm tắt...'),
(14, N'Nữ kiệt Tống Khánh...', N'Tường Hồng Bang', N'Tóm tắt...'),
(15, N'Trang sức người Việt...', N'Trịnh Sinh', N'Tóm tắt...');

-- Insert sample data into DauSach
INSERT INTO DauSach (isbn, ma_tuasach, ngonngu, bia, trangthai) VALUES
(1, 1, N'Anh', N'Bìa cứng', 'Y'),
(3, 1, N'Đức', N'Bìa cứng', 'Y'),
(4, 1, N'Hàn', N'Bìa cứng', 'Y'),
(5, 1, N'Hoa', N'Bìa cứng', 'Y'),
(6, 1, N'Nhật', N'Bìa cứng', 'Y'),
(7, 1, N'Pháp', N'Bìa cứng', 'Y'),
(9, 1, N'Việt', N'Bìa cứng', 'Y'),
(10, 1, N'Ý', N'Bìa cứng', 'Y'),
(11, 2, N'Anh', N'Bìa cứng', 'Y'),
(13, 2, N'Đức', N'Bìa cứng', 'Y'),
(14, 2, N'Hàn', N'Bìa cứng', 'Y'),
(15, 2, N'Hoa', N'Bìa cứng', 'Y'),
(16, 2, N'Nhật', N'Bìa cứng', 'Y'),
(17, 2, N'Pháp', N'Bìa cứng', 'Y'),
(19, 2, N'Việt', N'Bìa cứng', 'Y');

-- Insert sample data into CuonSach
INSERT INTO CuonSach (isbn, Ma_CuonSach, TinhTrang) VALUES
(1, 1, 'N'),
(1, 2, 'N'),
(1, 3, 'Y'),
(1, 4, 'N'),
(1, 5, 'Y'),
(3, 1, 'Y'),
(3, 2, 'N'),
(3, 3, 'N'),
(3, 4, 'N'),
(3, 5, 'N'),
(4, 1, 'N'),
(4, 2, 'N'),
(4, 3, 'N'),
(4, 4, 'N'),
(4, 5, 'Y');

-- Insert sample data into DocGia
INSERT INTO DocGia (ma_docgia, ho, tenlot, ten, NgaySinh) VALUES
(1, N'Phạm', N'V', N'Bảo', '1990-01-05'),
(2, N'Võ', N'V', N'Dũng', '2002-01-01'),
(3, N'Văn', N'P', N'Phúc', '1988-05-06'),
(4, N'Bùi', N'N', N'Bình', '2003-08-09'),
(5, N'Lê', N'V', N'Sang', '1982-09-26'),
(6, N'Võ', N'H', N'Hà', '2001-12-07'),
(7, N'Lê', N'B', N'Mộng', '1990-03-06'),
(8, N'Vũ', N'C', N'Hường', '2003-07-08'),
(9, N'Đinh', N'B', N'Hà', '1980-04-06'),
(10, N'Hồ', N'V', N'Mỹ', '2005-08-12'),
(11, N'Đinh', N'L', N'Mộng', '1970-06-09'),
(12, N'Đỗ', N'B', N'Phương', '2006-07-15'),
(13, N'Đồng', N'L', N'Bình', '1977-02-25'),
(14, N'Thân', N'P', N'Mỹ', '2004-11-09'),
(15, N'Phan', N'N', N'Mỹ', '1983-03-26'),
(17, N'Nguyễn', N'V', N'Hùng', '1985-05-15'),
(19, N'Trần', N'T', N'Minh', '1979-08-22'),
(21, N'Lê', N'H', N'Thảo', '1992-04-18'),
(23, N'Phạm', N'A', N'Tuấn', '1976-11-30'),
(25, N'Hoàng', N'B', N'Linh', '1989-09-12'),
(27, N'Vũ', N'C', N'Nam', '1981-02-28'),
(29, N'Đặng', N'T', N'Hương', '1987-07-19');

INSERT INTO DocGia (ma_docgia, ho, tenlot, ten, NgaySinh) VALUES
(30, N'Nguyễn', N'P', N'Hoàng', '2005-03-13');

-- Insert sample data into NguoiLon
INSERT INTO NguoiLon (ma_docgia, sonha, duong, quan, dienthoai, han_sd) VALUES
(1, N'10', N'Bùi Thị Xuân', N'2', NULL, '2014-06-20'),
(3, N'20', N'Đinh Bộ Lĩnh', N'4', NULL, '2015-03-22'),
(5, N'30', N'Dương Bá Trạc', N'6', NULL, '2015-05-10'),
(7, N'40', N'Huỳnh Khương Ninh', N'8', NULL, '2015-06-26'),
(9, N'50', N'Lê Lợi', N'10', NULL, '2015-06-28'),
(11, N'60', N'Lê Thị Riêng', N'BT', NULL, '2015-06-30'),
(13, N'70', N'Nguyễn Trãi', N'GV', NULL, '2015-07-02'),
(15, N'80', N'Phạm Ngũ Lão', N'TD', NULL, '2015-07-04'),
(17, N'10', N'Phan Bội Châu', N'2', NULL, '2015-05-20'),
(19, N'20', N'Trần Hưng Đạo', N'4', NULL, '2015-07-08'),
(21, N'30', N'Trần Phú', N'6', NULL, '2015-07-10'),
(23, N'40', N'An Dương Vương', N'8', NULL, '2015-07-12'),
(25, N'50', N'Cao Bá Quát', N'10', NULL, '2015-07-14'),
(27, N'60', N'Đào Duy Từ', N'BT', NULL, '2015-07-16'),
(29, N'70', N'Hoàng Hoa thám', N'GV', NULL, '2015-05-10');
INSERT INTO NguoiLon (ma_docgia, sonha, duong, quan, dienthoai, han_sd) VALUES
(30, N'05', N'Số 07', N'TD', NULL, '2015-05-10');

INSERT INTO DocGia (ma_docgia, ho, tenlot, ten, NgaySinh) VALUES
(16, N'Trần', N'V', N'Hải', '2005-02-10'),
(18, N'Nguyễn', N'T', N'Anh', '2006-05-15'),
(20, N'Lê', N'V', N'Hùng', '2004-08-20'),
(22, N'Phạm', N'H', N'Minh', '2007-03-25'),
(24, N'Vũ', N'T', N'Thảo', '2003-06-30'),
(26, N'Trần', N'M', N'Hoa', '2008-09-05'),
(28, N'Nguyễn', N'K', N'Linh', '2002-12-10');

-- Insert sample data into TreEm
INSERT INTO TreEm (ma_docgia, ma_docgia_nguoilon) VALUES
(2, 1),
(4, 3),
(6, 5),
(8, 7),
(10, 9),
(12, 11),
(14, 13),
(16, 15),
(18, 17),
(20, 19),
(22, 21),
(24, 23),
(26, 25),
(28, 27),
(30, 29);

INSERT INTO DocGia (ma_docgia, ho, tenlot, ten, NgaySinh) VALUES
(35, N'Nguyễn', N'V', N'An', '1985-06-15'),
(52, N'Trần', N'T', N'Bình', '1990-08-22'),
(69, N'Lê', N'H', N'Cường', '1992-04-18'),
(86, N'Phạm', N'A', N'Dũng', '1976-11-30');

-- Sau đó thêm vào NguoiLon (tùy thuộc vào yêu cầu)
INSERT INTO NguoiLon (ma_docgia, sonha, duong, quan, dienthoai, han_sd) VALUES
(35, N'15', N'Đường số 8', N'5', NULL, '2015-05-10'),
(52, N'25', N'Đường số 9', N'4', NULL, '2015-07-08'),
(69, N'35', N'Đường số 10', N'6', NULL, '2015-07-10'),
(86, N'45', N'Đường số 11', N'8', NULL, '2015-07-12');

-- Insert sample data into DangKy
INSERT INTO DauSach (isbn, ma_tuasach, ngonngu, bia, trangthai) VALUES
(43, 3, N'Anh', N'Bìa cứng', 'Y'),
(246, 4, N'Việt', N'Bìa mềm', 'Y'),
(330, 5, N'Pháp', N'Bìa cứng', 'Y'),
(533, 6, N'Nhật', N'Bìa mềm', 'Y'),
(575, 7, N'Hoa', N'Bìa cứng', 'Y'),
(617, 8, N'Đức', N'Bìa mềm', 'Y'),
(820, 9, N'Hàn', N'Bìa cứng', 'Y');

INSERT INTO DangKy (isbn, ma_docgia, ngaygio_dk, ghichu) VALUES
(1, 1, '2012-03-03 00:00:00', NULL),
(1, 52, '2012-03-03 00:00:00', NULL),
(43, 35, '2012-03-03 00:00:00', NULL),
(43, 86, '2012-03-03 00:00:00', NULL),
(246, 18, '2012-03-03 00:00:00', NULL),
(246, 69, '2012-03-03 00:00:00', NULL),
(330, 35, '2012-03-03 00:00:00', NULL),
(330, 86, '2012-03-03 00:00:00', NULL),
(533, 18, '2012-03-03 00:00:00', NULL),
(533, 69, '2012-03-03 00:00:00', NULL),
(575, 1, '2012-03-03 00:00:00', NULL),
(575, 52, '2012-03-03 00:00:00', NULL),
(617, 35, '2012-03-03 00:00:00', NULL),
(617, 86, '2012-03-03 00:00:00', NULL),
(820, 18, '2012-03-03 00:00:00', NULL);

-- Thêm các cuốn sách còn thiếu vào bảng CuonSach
INSERT INTO CuonSach (isbn, Ma_CuonSach, TinhTrang) VALUES
-- Thêm các cuốn sách của isbn 5
(5, 1, 'N'),
(5, 2, 'N'),
(5, 3, 'N'),
(5, 4, 'Y'),
(5, 5, 'N'),

-- Thêm các cuốn sách của isbn 6
(6, 1, 'N'),
(6, 2, 'N'),
(6, 3, 'Y'),
(6, 4, 'N'),
(6, 5, 'N'),

-- Thêm các cuốn sách của isbn 7
(7, 1, 'N'),
(7, 2, 'Y'),
(7, 3, 'N'),
(7, 4, 'N'),
(7, 5, 'N'),

-- Thêm các cuốn sách của isbn 9
(9, 1, 'N'),
(9, 2, 'N'),
(9, 3, 'N'),
(9, 4, 'N'),
(9, 5, 'Y'),

-- Thêm các cuốn sách của isbn 10
(10, 1, 'N'),
(10, 2, 'N'),
(10, 3, 'N'),
(10, 4, 'Y'),
(10, 5, 'N'),

-- Thêm các cuốn sách của isbn 11
(11, 1, 'N'),
(11, 2, 'N'),
(11, 3, 'Y'),
(11, 4, 'N'),
(11, 5, 'N'),

-- Thêm các cuốn sách của isbn 13
(13, 1, 'Y'),
(13, 2, 'N'),
(13, 3, 'N'),
(13, 4, 'N'),
(13, 5, 'N'),

-- Thêm các cuốn sách của isbn 14
(14, 1, 'N'),
(14, 2, 'N'),
(14, 3, 'N'),
(14, 4, 'N'),
(14, 5, 'Y'),

-- Thêm các cuốn sách của isbn 15
(15, 1, 'N'),
(15, 2, 'N'),
(15, 3, 'N'),
(15, 4, 'Y'),
(15, 5, 'N'),

-- Thêm các cuốn sách của isbn 16
(16, 1, 'N'),
(16, 2, 'N'),
(16, 3, 'Y'),
(16, 4, 'N'),
(16, 5, 'N'),

-- Thêm các cuốn sách của isbn 17
(17, 1, 'N'),
(17, 2, 'Y'),
(17, 3, 'N'),
(17, 4, 'N'),
(17, 5, 'N');

-- Insert sample data into Muon
INSERT INTO Muon (isbn, ma_cuonsach, ma_docgia, ngayGio_muon, ngay_hethan) VALUES
(1, 3, 2, '2014-02-06 00:00:00', '2014-02-20 00:00:00'),
(1, 5, 1, '2014-02-19 00:00:00', '2014-02-03 00:00:00'),
(3, 1, 1, '2014-02-06 00:00:00', '2014-02-20 00:00:00'),
(4, 5, 1, '2014-02-07 00:00:00', '2014-02-21 00:00:00'),
(5, 4, 1, '2014-02-07 00:00:00', '2014-02-21 00:00:00'),
(6, 3, 1, '2014-02-05 00:00:00', '2014-02-19 00:00:00'),
(7, 2, 1, '2014-03-13 00:00:00', '2014-03-01 00:00:00'),
(9, 5, 2, '2014-03-13 00:00:00', '2014-03-27 00:00:00'),
(10, 4, 2, '2014-03-11 00:00:00', '2014-03-25 00:00:00'),
(11, 3, 2, '2014-03-04 00:00:00', '2014-03-18 00:00:00'),
(13, 1, 2, '2014-03-13 00:00:00', '2014-03-27 00:00:00'),
(14, 5, 2, '2014-03-09 00:00:00', '2014-03-23 00:00:00'),
(15, 4, 2, '2014-03-13 00:00:00', '2014-03-27 00:00:00'),
(16, 3, 2, '2014-03-03 00:00:00', '2014-03-17 00:00:00'),
(17, 2, 2, '2014-03-05 00:00:00', '2014-03-19 00:00:00');

INSERT INTO Muon (isbn, ma_cuonsach, ma_docgia, ngayGio_muon, ngay_hethan) VALUES
-- Các bản ghi cần cho QuaTrinhMuon
(1, 3, 23, '2013-06-07 00:00:00', '2013-06-21 00:00:00'),
(1, 3, 23, '2013-06-21 00:00:00', '2013-07-05 00:00:00'),
(1, 3, 23, '2013-07-05 00:00:00', '2013-07-19 00:00:00'),
(1, 3, 23, '2013-07-19 00:00:00', '2013-08-02 00:00:00'),
(1, 3, 23, '2013-08-02 00:00:00', '2013-08-16 00:00:00'),
(1, 3, 23, '2013-08-16 00:00:00', '2013-08-30 00:00:00'),
(1, 3, 23, '2013-08-30 00:00:00', '2013-09-13 00:00:00'),
(1, 3, 23, '2013-09-13 00:00:00', '2013-09-27 00:00:00'),
(1, 3, 23, '2013-09-27 00:00:00', '2013-10-11 00:00:00'),
(1, 3, 23, '2013-10-11 00:00:00', '2013-10-25 00:00:00'),
(1, 3, 23, '2013-10-25 00:00:00', '2013-11-08 00:00:00'),
(1, 3, 23, '2013-11-08 00:00:00', '2013-11-22 00:00:00'),
(14, 5, 2, '2013-06-24 00:00:00', '2013-07-08 00:00:00'),
(14, 5, 2, '2013-07-08 00:00:00', '2013-07-22 00:00:00'),
(14, 5, 2, '2013-07-22 00:00:00', '2013-08-05 00:00:00');
-- Insert sample data into QuaTrinhMuon
INSERT INTO QuaTrinhMuon (isbn, ma_cuonsach, ngayGio_muon, ma_docgia, ngay_hethan, ngayGio_tra, tien_muon, tien_datra, tien_datcoc, ghichu) VALUES
(1, 3, '2013-06-07 00:00:00', 23, '2013-06-21 00:00:00', '2013-06-10 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-06-21 00:00:00', 23, '2013-07-05 00:00:00', '2013-06-24 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-07-05 00:00:00', 23, '2013-07-19 00:00:00', '2013-07-08 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-07-19 00:00:00', 23, '2013-08-02 00:00:00', '2013-07-22 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-08-02 00:00:00', 23, '2013-08-16 00:00:00', '2013-08-05 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-08-16 00:00:00', 23, '2013-08-30 00:00:00', '2013-08-19 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-08-30 00:00:00', 23, '2013-09-13 00:00:00', '2013-09-02 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-09-13 00:00:00', 23, '2013-09-27 00:00:00', '2013-09-16 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-09-27 00:00:00', 23, '2013-10-11 00:00:00', '2013-09-30 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-10-11 00:00:00', 23, '2013-10-25 00:00:00', '2013-10-14 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-10-25 00:00:00', 23, '2013-11-08 00:00:00', '2013-10-28 00:00:00', NULL, NULL, NULL, NULL),
(1, 3, '2013-11-08 00:00:00', 23, '2013-11-22 00:00:00', '2013-11-11 00:00:00', NULL, NULL, NULL, NULL),
(14, 5, '2013-06-24 00:00:00', 2, '2013-07-08 00:00:00', '2013-06-30 00:00:00', NULL, NULL, NULL, NULL),
(14, 5, '2013-07-08 00:00:00', 2, '2013-07-22 00:00:00', '2013-07-14 00:00:00', NULL, NULL, NULL, NULL),
(14, 5, '2013-07-22 00:00:00', 2, '2013-08-05 00:00:00', '2013-07-28 00:00:00', NULL, NULL, NULL, NULL);