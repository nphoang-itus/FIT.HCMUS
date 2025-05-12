-- MSSV: 23120264
-- Họ tên: Nguyễn Phúc Hoàng
-- Email: nphuchoang.itus@gmail.com
-- Ngày làm bài: 11/05/2025

USE [DB_QLDeTai_23120264]

-- Procedure 1 - Xuất ra toàn bộ danh sách giáo viên.
CREATE PROCEDURE sp_23120264_1
AS
    SELECT * FROM GIAOVIEN;
GO

EXEC sp_23120264_1;

-- Procedure 2 - Tính số lượng đề tài mà một giáo viên đang thực hiện.
CREATE PROCEDURE sp_23120264_2
    @MAGV VARCHAR(9)
AS
BEGIN
    SELECT @MAGV AS MAGV, COUNT(DISTINCT MADT) AS SLDETAI_DANGTHUCHIEN
    FROM THAMGIADT
    WHERE MAGV = @MAGV;
END;
GO

EXEC sp_23120264_2 '003';

-- Procedure 3 - In thông tin chi tiết của một giáo viên (sử dụng lệnh print): Thông tin cá nhân, số lượng đề tài tham gia, số lượng thân nhân của giáo viên đó.
CREATE PROCEDURE sp_23120264_3
    @MAGV VARCHAR(9)
AS
BEGIN
    DECLARE
        @HOTEN NVARCHAR(50),
        @SLDETAITHAMGIA INT,
        @SOLUONGTHANNHAN INT;
    
    SELECT @HOTEN = HOTEN
    FROM GIAOVIEN
    WHERE @MAGV = MaGV;

    SELECT @SLDETAITHAMGIA = COUNT(DISTINCT MADT)
    FROM THAMGIADT
    WHERE @MAGV = MaGV;

    SELECT @SOLUONGTHANNHAN = COUNT(TEN)
    FROM NGUOITHAN
    WHERE @MAGV = MaGV;

    PRINT '=== THONG TIN GIAO VIEN MA ' + @MAGV + ' ===';
    PRINT 'THONG TIN GIAO VIEN ' + @HOTEN;
    PRINT 'SO LUONG DE TAI THAM GIA ' + CAST(@SLDETAITHAMGIA AS VARCHAR);
    PRINT 'SO LUONG NGUOI THAN ' + CAST(@SOLUONGTHANNHAN AS VARCHAR);
END;
GO
EXEC sp_23120264_3 '003';

-- Procedure 4 - Kiểm tra xem một giáo viên có tồn tại hay không (dựa vào MAGV).
CREATE PROCEDURE sp_23120264_4
    @MAGV VARCHAR(9)
AS
BEGIN
    IF (EXISTS (SELECT 1 FROM GIAOVIEN WHERE MAGV = @MAGV))
        PRINT N'GIAO VIEN TON TAI'
    ELSE
        PRINT N'KHONG TON TAI GIAO VIEN ' + @MAGV
END;
GO

EXEC sp_23120264_4 '001';

-- Procedure 5 - Kiểm tra quy định của một giáo viên: Chỉ được thực hiện các đề tài mà bộ môn của giáo viên đó làm chủ nhiệm.
CREATE PROCEDURE sp_23120264_5
    @MAGV VARCHAR(9)
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM THAMGIADT TG JOIN GIAOVIEN GV ON GV.MAGV = TG.MAGV
        WHERE GV.MAGV = @MAGV AND TG.MADT NOT IN ( -- LẤY RA NHỮNG ĐỀ TÀI KO CHUNG BỘ MÔN VỚI GVCN
            SELECT TG2.MADT
            FROM THAMGIADT TG2
                JOIN DETAI DT ON DT.MADT = TG2.MADT
                JOIN GIAOVIEN GVCN ON DT.GVCNDT = GVCN.MAGV
            WHERE GVCN.MABM = GV.MABM
        )
    )
    BEGIN
        PRINT N'GIAO VIEN VI PHAM QUY DINH';
    END
    ELSE
    BEGIN
        PRINT N'GIAO VIEN KHONG VI PHAM QUY DINH';
    END;
END;
GO

EXEC sp_23120264_5 '003'

-- Procedure 6 - Thực hiện thêm một phân công cho giáo viên thực hiện một công việc của đề tài:
---- a. Kiểm tra thông tin đầu vào hợp lệ: giáo viên phải tồn tại, công việc phải tồn tại, thời gian tham gia phải > 0.
---- b. Kiểm tra quy định ở câu 5.
CREATE PROCEDURE sp_23120264_6
    @MAGV VARCHAR(9),
    @MADT VARCHAR(9),
    @STT INT,
    @PHUCAP FLOAT,
    @KETQUA NVARCHAR(9)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM GIAOVIEN WHERE MAGV = @MAGV)
    AND EXISTS (
        SELECT 1
        FROM CONGVIEC
        WHERE MADT = @MADT AND SOTT = @STT
    )
    AND EXISTS (
        SELECT 1
        FROM THAMGIADT TG JOIN GIAOVIEN GV ON GV.MAGV = TG.MAGV
        WHERE GV.MAGV = @MAGV AND TG.MADT NOT IN ( -- LẤY RA NHỮNG ĐỀ TÀI KO CHUNG BỘ MÔN VỚI GVCN
            SELECT TG2.MADT
            FROM THAMGIADT TG2
                JOIN DETAI DT ON DT.MADT = TG2.MADT
                JOIN GIAOVIEN GVCN ON DT.GVCNDT = GVCN.MAGV
            WHERE GVCN.MABM = GV.MABM
        )
    )
    -- AND (SELECT DATEDIFF(D, NGAYBD, NGAYKT) FROM CONGVIEC WHERE MADT = @MADT AND SOTT = @STT) > 0
    BEGIN
        INSERT INTO THAMGIADT (MAGV, MADT, STT, PHUCAP, KETQUA)
        VALUES (@MAGV, @MADT, @STT, @PHUCAP, @KETQUA)
    END
    ELSE
    BEGIN
        RAISERROR (N'KHONG THEM DUOC CONG VIEC', 16, 1)
    END;
END;
GO

EXEC sp_23120264_6 '001', '006', 1, 1.2, 'NULL'

-- Procedure 7 - Thực hiện xoá một giáo viên theo mã. Nếu giáo viên có thông tin liên quan (có thân nhân, có làm đề tài, …) thì báo lỗi.
CREATE OR ALTER PROCEDURE sp_23120264_7
    @MAGV VARCHAR(9)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM NGUOITHAN WHERE MAGV = @MAGV)
    BEGIN
        RAISERROR (N'LOI: TON TAI NGUOI THAN', 16, 1);
        RETURN;
    END;
    
    IF EXISTS (SELECT 1 FROM THAMGIADT WHERE MAGV = @MAGV)
    BEGIN
        RAISERROR (N'LOI: CO THAM GIA DE TAI', 16, 1);
        RETURN
    END;

    IF EXISTS (SELECT 1 FROM BOMON WHERE TruongBM = @MAGV)
    BEGIN
        RAISERROR (N'LOI: GIAO VIEN LAM TRUONG BO MON', 16, 1);
        RETURN
    END;

    DELETE FROM GIAOVIEN WHERE MAGV = @MAGV;
END;
GO

EXEC sp_23120264_7 '005'

-- Procedure 8 - In ra danh sách giáo viên của một khoa nào đó cùng với số lượng đề tài mà giáo viên tham gia, số thân nhân, số giáo viên mà giáo viên đó quản lý nếu có, …
CREATE OR ALTER PROCEDURE sp_23120264_8
    @MAKHOA VARCHAR(9)
AS
BEGIN
    SELECT DISTINCT
        GV.MAGV, GV.HOTEN,
        COUNT(DISTINCT TG.MADT) AS SL_DETAI,
        COUNT(DISTINCT NT.TEN) AS SL_NGUOITHAN,
        COUNT(DISTINCT GVQL.GVQLCM) AS SL_GVQL
    FROM GIAOVIEN GV
        LEFT JOIN THAMGIADT TG ON TG.MAGV = GV.MAGV
        LEFT JOIN NGUOITHAN NT ON NT.MAGV = GV.MAGV
        LEFT JOIN GIAOVIEN GVQL ON GVQL.GVQLCM = GV.MAGV
        JOIN BOMON BM ON GV.MABM = BM.MABM
        JOIN KHOA K ON K.MAKHOA = BM.MAKHOA
    WHERE K.MAKHOA = @MAKHOA
    GROUP BY GV.MAGV, GV.HOTEN;
END;
GO

EXEC sp_23120264_7 'CNTT'

-- Procedure 9 - Kiểm tra quy định của 2 giáo viên a, b: Nếu a là trưởng bộ môn c của b thì lương của a phải cao hơn lương của b. (a, b: mã giáo viên)
CREATE OR ALTER PROCEDURE sp_23120264_9
    @A VARCHAR(9),
    @B VARCHAR(9)
AS
BEGIN
    IF ((SELECT MABM FROM GIAOVIEN WHERE MAGV = @A) != (SELECT MABM FROM GIAOVIEN WHERE MAGV = @B))
    BEGIN
        PRINT N'HAI GIAO VIEN KHONG CUNG BO MON';
        RETURN;
    END
    
    IF (@A != (SELECT BM.TRUONGBM FROM BOMON BM JOIN GIAOVIEN GV ON GV.MABM = BM.MABM WHERE GV.MAGV = @B))
    BEGIN
        PRINT N'GIAO VIEN ' + @A + ' KHONG PHAI TRUONG BO MON CUA GIAO VIEN ' + @B;
        RETURN;
    END
    
    IF ((SELECT LUONG FROM GIAOVIEN WHERE MAGV = @A) > (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @B))
    BEGIN
        PRINT N'THOA QUY DINH 2 GIAO VIEN ' + @A + ' VA ' + @B;
    END
    ELSE
    BEGIN
        RAISERROR (N'LOI: 2 GIAO VIEN KHONG THOA QUY DINH', 16, 1);
    END;
END;
GO

EXEC sp_23120264_8 '001','002'

-- Procedure 10 - Thêm một giáo viên: Kiểm tra các quy định: Không trùng tên, tuổi > 18, lương > 0.
CREATE OR ALTER PROCEDURE sp_23120264_10
    @MAGV VARCHAR(9),
    @HOTEN NVARCHAR(30),
    @LUONG FLOAT,
    @PHAI NVARCHAR(3),
    @NGSINH DATE,
    @DIACHI NVARCHAR(50),
    @GVQLCM VARCHAR(9),
    @MABM NVARCHAR(9)
AS
BEGIN
    IF @HOTEN IN (SELECT HOTEN FROM GIAOVIEN)
    BEGIN
        RAISERROR (N'LOI: GIAO VIEN TRUNG TEN', 16, 1);
        RETURN;
    END;

    IF (YEAR(GETDATE()) - YEAR(@NGSINH) <= 18)
    BEGIN
        RAISERROR (N'LOI: GIAO VIEN NHO HON 18 TUOI', 16, 1);
        RETURN;
    END;

    IF (@LUONG <= 0)
    BEGIN
        RAISERROR (N'LOI: LUONG PHAI LON HON 0', 16, 1);
        RETURN;
    END;

    INSERT INTO GIAOVIEN (MAGV, HOTEN, LUONG, NGSINH, DIACHI, GVQLCM, MABM)
    VALUES (@MAGV, @HOTEN, @LUONG, @NGSINH, @DIACHI, @GVQLCM, @MABM)
END;
GO
EXEC sp_23120264_10 '012', N'Phúc Hoàng', 12000.0, 'Nam', '2005-03-13', '05, Đường số 07, Linh Chiểu, Thủ Đức, TP.HCM', '001', 'MMT'
EXEC sp_23120264_10 '012', N'Phúc Hon', 12000.0, 'Nam', '2023-03-13', '05, Đường số 07, Linh Chiểu, Thủ Đức, TP.HCM', '001', 'MMT'

-- Procedure 11 - Mã giáo viên được xác định tự động theo quy tắc: nếu đã có giáo viên 001, 002, 003 thì MAGV của giáo viên mới là 004. Nếu đã có giáo viên 001, 002, 005 thì MAGV của giáo viên mới là 003.
CREATE OR ALTER PROCEDURE sp_23120264_11
AS
BEGIN
    DECLARE @MAGV VARCHAR(9);
    DECLARE @COUNTER INT = 1;

    DECLARE @EXISTINGIDS TABLE (MAGV VARCHAR(9));
    INSERT INTO @EXISTINGIDS SELECT MAGV FROM GIAOVIEN;

    /*
        '000' + COUNTER
        VD COUNTER = 12 => '000' + COUNTER (PHẢI ÉP VỀ KIỂU VARCHAR) => 00012
        RIGHT(..., N) => LẤY N KÝ TỰ TỪ BÊN PHẢI => LẤY 3 KÝ TỰ TỪ BÊN PHẢI => 012
    */
    WHILE EXISTS (SELECT 1 FROM @EXISTINGIDS WHERE MAGV = RIGHT('000' + CAST(@COUNTER AS VARCHAR(3)), 3))
    BEGIN
        SET @COUNTER = @COUNTER + 1;
    END;

    SET @MAGV = RIGHT('000' + CAST(@COUNTER AS VARCHAR(9)), 3);
    PRINT N'GIAO VIEN SE DUOC CAP MA: ' + @MAGV;
END;
GO

EXEC sp_23120264_11