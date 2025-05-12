-- MSSV: 23120264
-- Họ tên: Nguyễn Phúc Hoàng
-- Email: nphuchoang.itus@gmail.com
-- Ngày làm bài: 11/05/2025

CREATE DATABASE QL_DATPHONG;
GO

USE QL_DATPHONG;
GO

CREATE TABLE PHONG (
    MAPHONG VARCHAR(9),
    TINHTRANG NVARCHAR(4) CHECK (TINHTRANG IN (N'Rãnh', N'Bận')),
    LOAIPHONG NVARCHAR(15),
    DONGIA INT

    PRIMARY KEY (MAPHONG)
);
GO

CREATE TABLE KHACHHANG (
    MAKH VARCHAR(9),
    HOTEN NVARCHAR(30),
    DIACHI NVARCHAR(50),
    DIENTHOAI VARCHAR(11)

    PRIMARY KEY (MAKH)
);
GO

CREATE TABLE DATPHONG (
    MADP INT IDENTITY(1, 1),
    MAKH VARCHAR(9),
    MAPHONG VARCHAR(9),
    NGAYDP DATE,
    NGAYTRA DATE,
    THANHTIEN INT

    PRIMARY KEY (MADP)
);
GO

ALTER TABLE DATPHONG ADD
    CONSTRAINT FK_DATPHONG_MAKH FOREIGN KEY (MAKH) REFERENCES KHACHHANG(MAKH),
    CONSTRAINT FK_DATPHONG_MAPHONG FOREIGN KEY (MAPHONG) REFERENCES PHONG(MAPHONG);
GO

-- Insert sample data into PHONG table
INSERT INTO PHONG (MAPHONG, TINHTRANG, LOAIPHONG, DONGIA)
VALUES 
    ('P001', N'Rãnh', N'Phòng đơn', 300000),
    ('P002', N'Rãnh', N'Phòng đôi', 500000),
    ('P003', N'Bận', N'Phòng đơn', 350000),
    ('P004', N'Bận', N'Phòng gia đình', 800000),
    ('P005', N'Rãnh', N'Phòng đôi', 550000),
    ('P006', N'Rãnh', N'Phòng VIP', 1200000),
    ('P007', N'Bận', N'Phòng đơn', 320000),
    ('P008', N'Rãnh', N'Phòng gia đình', 750000),
    ('P009', N'Rãnh', N'Phòng VIP', 1500000),
    ('P010', N'Bận', N'Phòng đôi', 520000);
GO

-- Insert sample data into KHACHHANG table
INSERT INTO KHACHHANG (MAKH, HOTEN, DIACHI, DIENTHOAI)
VALUES 
    ('KH001', N'Nguyễn Văn An', N'123 Nguyễn Trãi, Q1, TP.HCM', '0901234567'),
    ('KH002', N'Trần Thị Bình', N'456 Lê Lợi, Q3, TP.HCM', '0912345678'),
    ('KH003', N'Lê Văn Cường', N'789 Cách Mạng Tháng 8, Q10, TP.HCM', '0923456789'),
    ('KH004', N'Phạm Thị Dung', N'101 Võ Văn Ngân, Thủ Đức, TP.HCM', '0934567890'),
    ('KH005', N'Hoàng Văn Em', N'202 Lý Thường Kiệt, Q10, TP.HCM', '0945678901'),
    ('KH006', N'Ngô Thị Phương', N'303 Điện Biên Phủ, Bình Thạnh, TP.HCM', '0956789012'),
    ('KH007', N'Đặng Văn Giang', N'404 Nguyễn Văn Cừ, Q5, TP.HCM', '0967890123'),
    ('KH008', N'Vũ Thị Hoa', N'505 Phan Đình Phùng, Phú Nhuận, TP.HCM', '0978901234'),
    ('KH009', N'Bùi Văn Inh', N'606 Nguyễn Kiệm, Gò Vấp, TP.HCM', '0989012345'),
    ('KH010', N'Lý Thị Kim', N'707 Phan Chu Trinh, Q1, TP.HCM', '0990123456');
GO

-- Insert sample data into DATPHONG table
INSERT INTO DATPHONG (MAKH, MAPHONG, NGAYDP, NGAYTRA, THANHTIEN)
VALUES 
    ('KH001', 'P001', '2025-05-01', '2025-05-03', 600000),
    ('KH002', 'P003', '2025-05-02', '2025-05-05', 1050000),
    ('KH003', 'P007', '2025-05-03', '2025-05-06', 960000),
    ('KH004', 'P004', '2025-05-04', '2025-05-10', 4800000),
    ('KH005', 'P002', '2025-05-10', '2025-05-12', 1000000),
    ('KH006', 'P010', '2025-05-15', '2025-05-18', 1560000),
    ('KH007', 'P005', '2025-05-20', '2025-05-22', 1100000),
    ('KH008', 'P006', '2025-06-01', '2025-06-05', 4800000),
    ('KH009', 'P008', '2025-06-10', '2025-06-15', 3750000),
    ('KH010', 'P009', '2025-06-20', '2025-06-25', 7500000);
GO

-- Implement stored procedure
CREATE OR ALTER PROCEDURE spDatPhong_23120264
    @MAKH VARCHAR(9),
    @MAPHONG VARCHAR(9),
    @NGAYDAT DATE
AS
BEGIN
    -- Kiểm tra mã khách hàng phải hợp lệ (tồn tại trong bảng Khách hàng)
    IF NOT EXISTS (SELECT 1 FROM KHACHHANG WHERE MAKH = @MAKH)
    BEGIN
        RAISERROR (N'LOI: KHONG TON TAI KHACH HANG CO MA %s', 16, 1, @MAKH);
        RETURN;
    END;

    -- Kiểm tra mã phòng hợp lệ (phải xuất hiện trong bảng Phòng)
    IF NOT EXISTS (SELECT 1 FROM PHONG WHERE MAPHONG = @MAPHONG)
    BEGIN
        RAISERROR (N'LOI: KHONG TON TAI PHONG CO MA %s', 16, 1, @MAPHONG);
        RETURN;
    END;

    -- Chỉ được đặt khi tình trạng phòng là 'Rảnh'
    IF (SELECT TINHTRANG FROM PHONG WHERE MAPHONG = @MAPHONG) NOT LIKE N'Rãnh'
    BEGIN
        RAISERROR (N'LOI: PHONG %s HIEN CO TINH TRANG BAN', 16, 1, @MAPHONG);
        RETURN;
    END;

    -- Ghi nhận thông tin đặt phòng (ngày trả và thành tiền là NULL)
    INSERT INTO DATPHONG (MAKH, MAPHONG, NGAYDP, NGAYTRA, THANHTIEN)
    VALUES  (@MAKH, @MAPHONG, @NGAYDAT, NULL, NULL);

    -- Cập nhật tình trạng của phòng là 'Bận'
    UPDATE PHONG
    SET TINHTRANG = N'Bận'
    WHERE MAPHONG = @MAPHONG;
END;
GO

-- Thực thi procedure trên
---- Testcase 1: Mã khách hàng không tồn tại trong bảng khách hàng
EXEC spDatPhong_23120264 'KH011', 'P001', '2025-05-12';

---- Testcase 2: Mã phòng không tồn tại trong bảng phòng
EXEC spDatPhong_23120264 'KH001', 'P011', '2025-05-12';

---- Testcase 3: Đặt phòng có tình trạng 'Bận'
EXEC spDatPhong_23120264 'KH001', 'P003', '2025-05-12';

---- Testcase 4: Đặt phòng thành công
EXEC spDatPhong_23120264 'KH001', 'P001', '2025-05-12';
GO
------ Kiểm tra tình trạng phòng sau khi đặt
SELECT MAPHONG, TINHTRANG FROM PHONG WHERE MAPHONG = 'P001'