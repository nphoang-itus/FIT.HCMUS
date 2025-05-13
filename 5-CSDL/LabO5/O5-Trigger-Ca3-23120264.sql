-- MSSV: 23120264
-- Họ tên: Nguyễn Phúc Hoàng
-- Email: nphuchoang.itus@gmail.com
-- Ngày làm bài: 12/05/2025

-- USE DB_QLDeTai_23120264;
-- GO

-- Trigger 1: Tên đề tài phải duy nhất.
/*
PHÂN TÍCH:
            T   |   X   |   S   
DETAI   |   +   |   -   |   +(TENDT)
*/
CREATE TRIGGER tg_23120264_R1
ON DETAI
FOR INSERT, UPDATE
AS
IF UPDATE(TENDT)
BEGIN
    IF EXISTS (
        SELECT TENDT
        FROM DETAI
        GROUP BY TENDT
        HAVING COUNT(*) > 1
    )
    BEGIN
        RAISERROR(N'TEN DE TAI PHAI LA DUY NHAT', 16, 1);
        ROLLBACK
    END;
END;
GO

SELECT * FROM DETAI

insert into DETAI (MaDT, TenDT, CapQL, KinhPhi, NgayBD, NgayKT, MaCD, GVCNDT) 
    values ('009', N'HTTT quản lý thư viện ở các trường ĐH', N'Trường', 20.0, '2009-05-10', '2010-05-10', 'QLGD', '001');
GO

-- Trigger 2: Trưởng bộ môn phải sinh trước 1975.
/* PHÂN TÍCH:
            T   |   X   |   S   
BOMON   |   +   |   -   |   +(TRUONGBM)
GIAOVIEN|   -   |   -   |   +(NGSINH)
*/

CREATE OR ALTER TRIGGER tg_23120264_R2_BOMON
ON BOMON
FOR INSERT, UPDATE
AS
IF UPDATE(TRUONGBM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN GIAOVIEN GV ON GV.MAGV = I.TRUONGBM
        WHERE I.TRUONGBM IS NOT NULL AND YEAR(GV.NGSINH) >= 1975
    )
    BEGIN
        RAISERROR('Trưởng bộ môn phải sinh trước năm 1975.', 16, 1);
        ROLLBACK;
    END;
END;
GO

CREATE OR ALTER TRIGGER tg_23120264_R2_GIAOVIEN
ON GIAOVIEN
FOR UPDATE
AS
IF UPDATE(NGSINH)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN BOMON BM ON BM.TRUONGBM = I.MAGV
        WHERE YEAR(NGSINH) >= 1975
    )
    BEGIN
        RAISERROR('Trưởng bộ môn phải sinh trước năm 1975.', 16, 1);
        ROLLBACK;
    END;
END;
GO

-- Trigger 3: Một bộ môn có tối thiểu 1 giáo viên nữ.
/* PHÂN TÍCH:
            T   |   X   |   S
GIAOVIEN|   -   |   +   |   +(PHAI, MABM)
*/

CREATE OR ALTER TRIGGER tg_23120264_R3
ON GIAOVIEN
FOR DELETE, UPDATE
AS
BEGIN
    -- Lấy danh sách bộ môn bị ảnh hưởng
    DECLARE @AffectedBomon TABLE (MaBM NVARCHAR(4))

    -- Trường hợp DELETE
    IF EXISTS (SELECT * FROM deleted WHERE PHAI = N'Nữ')
    BEGIN
        INSERT INTO @AffectedBomon(MaBM)
        SELECT DISTINCT MaBM FROM deleted
        WHERE MaBM IS NOT NULL AND PHAI = N'Nữ'
    END
    
    -- Trường hợp UPDATE PHAI hoặc MABM
    IF (UPDATE(PHAI) OR UPDATE(MABM)) AND EXISTS(SELECT * FROM inserted)
    BEGIN
        -- Thêm bộ môn từ deleted khi giáo viên chuyển bộ môn hoặc đổi phái
        INSERT INTO @AffectedBomon(MaBM)
        SELECT DISTINCT d.MaBM 
        FROM deleted d
        WHERE d.MaBM IS NOT NULL AND 
              (d.PHAI = N'Nữ' OR EXISTS(SELECT 1 FROM inserted i WHERE i.MAGV = d.MAGV AND i.PHAI != d.PHAI))
    END
    
    -- Kiểm tra mỗi bộ môn phải có ít nhất 1 giáo viên nữ
    IF EXISTS (
        SELECT ab.MaBM
        FROM @AffectedBomon ab
        LEFT JOIN (
            SELECT MaBM, COUNT(*) AS SoGVNu
            FROM GIAOVIEN
            WHERE PHAI = N'Nữ'
            GROUP BY MaBM
        ) gvnu ON ab.MaBM = gvnu.MaBM
        WHERE gvnu.SoGVNu IS NULL OR gvnu.SoGVNu < 1
    )
    BEGIN
        RAISERROR(N'ERROR: MỖI BỘ MÔN PHẢI CÓ ÍT NHẤT 1 GIÁO VIÊN NỮ', 16, 1);
        ROLLBACK;
    END
END;
GO

-- Trigger 4: Một giáo viên phải có ít nhất 1 số điện thoại.
/* PHÂN TÍCH
    GV_DT {
        T: -
        X: +
        S: MAGV
    }
*/

CREATE OR ALTER TRIGGER tg_23120264_R4
ON GV_DT
FOR DELETE, UPDATE
AS
BEGIN
    -- LẤY DANH SÁCH GIÁO VIÊN BỊ ẢNH HƯỞNG
    DECLARE @THAYDOI_GV TABLE (MAGV VARCHAR(9))
    INSERT INTO @THAYDOI_GV
    SELECT DISTINCT MAGV FROM DELETED

    IF EXISTS (
        SELECT 1
        FROM @THAYDOI_GV GV
        LEFT JOIN (
            SELECT MAGV, COUNT(DIENTHOAI) AS SL_SDT
            FROM GV_DT
            GROUP BY MAGV
        ) COUNT_SDT ON COUNT_SDT.MAGV = GV.MAGV
        WHERE COUNT_SDT.SL_SDT IS NULL OR COUNT_SDT.SL_SDT < 1
    )
    BEGIN
        RAISERROR (N'GIAO VIEN PHAI CO IT NHAT MOT SO DIEN THOAI', 16, 1);
        ROLLBACK;
    END;
END;
GO

-- Trigger 5: Một giáo viên có tối đa 3 số điện thoại.
CREATE OR ALTER TRIGGER tg_23120264_R5
ON GV_DT
FOR INSERT, UPDATE
AS
BEGIN
    -- LẤY DANH SÁCH GIÁO VIÊN BỊ ẢNH HƯỞNG
    DECLARE @THAYDOI_GV TABLE (MAGV VARCHAR(9))
    INSERT INTO @THAYDOI_GV
    SELECT DISTINCT MAGV FROM INSERTED

    IF EXISTS (
        SELECT 1
        FROM @THAYDOI_GV GV
        LEFT JOIN (
            SELECT MAGV, COUNT(DIENTHOAI) AS SL_SDT
            FROM GV_DT
            GROUP BY MAGV
        ) COUNT_SDT ON COUNT_SDT.MAGV = GV.MAGV
        WHERE COUNT_SDT.SL_SDT > 3
    )
    BEGIN
        RAISERROR (N'GIAO VIEN CO TOI DA 3 SO DIEN THOAI', 16, 1);
        ROLLBACK;
    END;
END;
GO

-- Trigger 6: Một bộ môn phải có tối thiểu 4 giáo viên.
/* PHÂN TÍCH
    GIAOVIEN {
        T: -
        X: +
        S: + (MABM)
    }
*/
CREATE OR ALTER TRIGGER tg_23120264_R6
ON GIAOVIEN
FOR DELETE, UPDATE
AS
IF UPDATE(MABM)
BEGIN
    DECLARE @MABM_BITHAYDOI TABLE (MABM VARCHAR(9));
    INSERT INTO @MABM_BITHAYDOI SELECT DISTINCT MABM FROM DELETED;

    IF EXISTS (
        SELECT 1
        FROM @MABM_BITHAYDOI BMTD
        LEFT JOIN GIAOVIEN GV ON BMTD.MABM = GV.MABM
        GROUP BY BMTD.MABM
        HAVING COUNT(GV.MAGV) < 4
    )
    BEGIN
        RAISERROR (N'BO MON DANG IT HON 4 GIAO VIEN', 16, 1);
        ROLLBACK;
    END;
END;
GO

-- Trigger 7: Trưởng bộ môn phải là người lớn tuổi nhất trong bộ môn.
/*
    BOMON {
        T: -
        X: -
        S: + (TRUONGBM)
    }

    GIAOVIEN {
        T: -
        X: -
        S: + (NGSINH)
    }
*/

CREATE OR ALTER TRIGGER tg_23120264_R7_BOMON
ON BOMON
FOR UPDATE
AS
BEGIN
    DECLARE @MABM_THAYDOI TABLE (MABM NVARCHAR(9), TRGBM VARCHAR(9));
    INSERT INTO @MABM_THAYDOI SELECT DISTINCT MABM, TruongBM FROM INSERTED;

    IF EXISTS (
        SELECT 1
        FROM @MABM_THAYDOI TD
        JOIN GIAOVIEN TRUONGBM ON TD.TRGBM = TRUONGBM.MaGV
        WHERE TD.TRGBM IS NOT NULL AND YEAR(TRUONGBM.NgSinh) > ANY (
            SELECT YEAR(GV.NGSINH)
            FROM GIAOVIEN GV
            WHERE GV.MaBM = TD.MABM AND GV.MAGV != TRUONGBM.MAGV
        )
    )
    BEGIN
        RAISERROR (N'TRUONG BO MON PHAI CO TUOI LON NHAT', 16, 1);
        ROLLBACK;
    END;
END;
GO

SELECT * FROM GIAOVIEN
SELECT * FROM BOMON
UPDATE BOMON SET TruongBM = '001' WHERE MABM = 'MMT'
GO

CREATE OR ALTER TRIGGER tg_23120264_R7_GIAOVIEN
ON GIAOVIEN
FOR UPDATE
AS
IF UPDATE(NGSINH)
BEGIN
    DECLARE @MAGV_THAYDOI TABLE (MAGV VARCHAR(9), NGSINH DATE, MABM VARCHAR(9));
    INSERT INTO @MAGV_THAYDOI SELECT DISTINCT MAGV, NGSINH, MABM FROM INSERTED;

    IF NOT EXISTS (
        SELECT 1 FROM @MAGV_THAYDOI TD WHERE TD.MAGV = (
            SELECT BM.TRUONGBM
            FROM BOMON BM
            WHERE BM.MABM = TD.MABM
        )
    )
    RETURN;
    
    IF EXISTS (
        SELECT 1
        FROM @MAGV_THAYDOI TD
        WHERE YEAR(TD.NGSINH) > ANY (
            SELECT YEAR(GV.NGSINH)
            FROM GIAOVIEN GV
            WHERE GV.MABM = TD.MABM AND GV.MAGV != TD.MAGV
        )
    )
    BEGIN
        RAISERROR (N'TRUONG BO MON PHAI CO TUOI LON NHAT', 16, 1);
        ROLLBACK;
    END;
END;

UPDATE GIAOVIEN SET NGSINH = '1976-12-3' WHERE MAGV = '002'
GO

-- Trigger 8: Nếu một giáo viên đã là trưởng bộ môn thì giáo viên đó không làm người quản lý chuyên môn.
/*
    GIAOVIEN {
        I: +
        D: -
        U: + (GVQLCM, MABM)
    }

    BOMON {
        I: +
        D: -
        U: + (TRUONGBM)
    }
*/
CREATE OR ALTER TRIGGER tg_23120264_R8_GIAOVIEN
ON GIAOVIEN
FOR INSERT, UPDATE
AS
IF UPDATE(GVQLCM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        WHERE I.GVQLCM IS NOT NULL AND I.GVQLCM IN (
            SELECT DISTINCT TRUONGBM
            FROM BOMON
        )
    )
    BEGIN
        RAISERROR (N'GIAO VIEN QUAN LY CHUYEN MON THI KHONG LAM TRUONG BO MON', 16, 1)
        ROLLBACK
    END;
END;
GO

CREATE OR ALTER TRIGGER tg_23120264_R8_BOMON
ON BOMON
FOR INSERT, UPDATE
AS
IF UPDATE(TRUONGBM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        WHERE I.TruongBM IS NOT NULL AND I.TRUONGBM IN (
            SELECT DISTINCT GVQLCM
            FROM GIAOVIEN
        )
    )
    BEGIN
        RAISERROR (N'GIAO VIEN QUAN LY CHUYEN MON THI KHONG LAM TRUONG BO MON', 16, 1)
        ROLLBACK
    END;
END;
GO

-- Trigger 9: Giáo viên và giáo viên quản lý chuyên môn của giáo viên đó phải thuộc về 1 bộ môn.
/*
    GIAOVIEN {
        I: +
        D: -
        U: + (GVQLCM) OR (MABM)
    }
*/
CREATE OR ALTER TRIGGER tg_23120264_R9
ON GIAOVIEN
FOR INSERT, UPDATE
AS
IF UPDATE(GVQLCM) OR UPDATE(MABM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        LEFT JOIN GIAOVIEN GVQL ON I.GVQLCM = GVQL.MAGV
        WHERE GVQL.MaGV IS NOT NULL AND I.MaBM != GVQL.MaBM
    )
    BEGIN
        RAISERROR (N'GIAO VIEN VA GVQLCM PHAI CUNG THUOC 1 BO MON', 16, 1)
        ROLLBACK
    END;
END;
GO

-- UPDATE GIAOVIEN SET GVQLCM = '003' WHERE MAGV = '007'

/*
-- CÂU TRIGGER NÀY KO CÓ DỮ LIỆU ĐỂ THỰC HIỆN (TRONG BẢNG NGƯỜI THÂN HAY BẤT KỲ BẢNG NÀO KO CÓ THUỘC TÍNH QUAN HỆ)
-- Trigger 10: Mỗi giáo viên chỉ có tối đa 1 vợ/chồng.
-- Trigger 11: Giáo viên là Nam thì chỉ có vợ/chồng là Nữ hoặc ngược lại.
-- Trigger 12: Nếu thân nhân có quan hệ là "con gái" hoặc "con trai" với giáo viên thì năm sinh của giáo viên phải nhỏ hơn năm sinh của thân nhân.
*/

-- Trigger 13: Một giáo viên chỉ làm chủ nhiệm tối đa 3 đề tài.
CREATE OR ALTER TRIGGER tg_23120264_R13
ON DETAI
FOR INSERT, UPDATE
AS
IF UPDATE(GVCNDT)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I JOIN DETAI DT ON DT.GVCNDT = I.GVCNDT
        GROUP BY (DT.GVCNDT)
        HAVING COUNT(DISTINCT DT.MADT) > 3
    )
    BEGIN
        RAISERROR (N'GIAO VIEN CHI LAM CHU NHIEM TOI DA 3 DE TAI', 16, 1)
        ROLLBACK
    END;
END;

UPDATE DETAI SET GVCNDT = '004' WHERE MADT = '005';
GO

-- Trigger 14: Một đề tài phải có ít nhất một công việc.
CREATE OR ALTER TRIGGER tg_23120264_R14
ON CONGVIEC
FOR DELETE, UPDATE
AS
BEGIN
    -- Lấy các đề tài có công việc bị xóa
    DECLARE @AffectedDeTai TABLE (MADT VARCHAR(3))
    INSERT INTO @AffectedDeTai
    SELECT DISTINCT MADT FROM DELETED

    -- Kiểm tra số công việc còn lại
    IF EXISTS (
        SELECT 1
        FROM @AffectedDeTai AD
        LEFT JOIN (
            SELECT MADT, COUNT(*) AS SoLuongCV
            FROM CONGVIEC
            GROUP BY MADT
        ) CV ON CV.MADT = AD.MADT
        WHERE CV.SoLuongCV IS NULL OR CV.SoLuongCV = 0
    )
    BEGIN
        RAISERROR (N'DE TAI PHAI CO IT NHAT MOT CONG VIEC', 16, 1)
        ROLLBACK
    END;
END;
GO

-- Trigger 15: Lương của giáo viên phải nhỏ hơn lương người quản lý của giáo viên đó.
CREATE OR ALTER TRIGGER tg_23120264_R15
ON GIAOVIEN
FOR INSERT, UPDATE
AS
IF UPDATE(LUONG) OR UPDATE(GVQLCM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN GIAOVIEN GVCN ON I.GVQLCM = GVCN.MAGV
        WHERE I.GVQLCM IS NOT NULL AND I.Luong > GVCN.Luong 
    )
    BEGIN
        RAISERROR (N'LUONG GV PHAI NHO HON GVQLCM', 16, 1)
        ROLLBACK
    END;
END;
GO

-- Trigger 16: Lương của trưởng bộ môn phải lớn hơn lương của các giáo viên trong bộ môn.
CREATE OR ALTER TRIGGER tg_23120264_R16_GIAOVIEN
ON GIAOVIEN
FOR INSERT, UPDATE
AS
IF UPDATE(LUONG) OR UPDATE(MABM)
BEGIN
    -- TH GV DANG CHON LA GVCNBM
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        WHERE I.MAGV = (
            SELECT TRUONGBM FROM BOMON WHERE MABM = I.MABM
        ) AND I.LUONG < ANY (
            SELECT LUONG
            FROM GIAOVIEN
            WHERE MABM = I.MABM AND MAGV != I.MAGV
        )
    )
    BEGIN
        RAISERROR (N'LUONG TRUONG BO MON PHAI LON HON LUONG GIAO VIEN TRONG BO MON', 16, 1);
        ROLLBACK;
        RETURN;
    END;

    -- TH GV DANG CHON KHONG LA GVCNBM
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        WHERE I.LUONG >= ALL (
            SELECT LUONG
            FROM GIAOVIEN
            WHERE MABM = I.MABM AND MAGV != I.MAGV
        )
    )
    BEGIN
        RAISERROR (N'LUONG TRUONG BO MON PHAI LON HON LUONG GIAO VIEN TRONG BO MON', 16, 1);
        ROLLBACK;
    END;
END;
GO

CREATE OR ALTER TRIGGER tg_23120264_R16_BOMON
ON BOMON
FOR UPDATE
AS
IF UPDATE(TRUONGBM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN GIAOVIEN TRGBM ON I.TRUONGBM = TRGBM.MAGV
        WHERE I.TruongBM IS NOT NULL AND TRGBM.LUONG < ANY (
            SELECT LUONG
            FROM GIAOVIEN
            WHERE MABM = TRGBM.MABM
        )
    )
    BEGIN
        RAISERROR (N'LUONG TRUONG BO MON PHAI LON HON LUONG GIAO VIEN TRONG BO MON', 16, 1);
        ROLLBACK;
    END;
END;
GO

-- CÂU TRIGGER NÀY THIẾU DỮ LIỆU (KHÔNG CÓ BẢNG BAN; KHÔNG CÓ THUỘC TÍNH TRƯỜNG HỌC)
-- Trigger 17: Bộ môn ban nào cũng phải có trưởng bộ môn và trưởng bộ môn phải là một giáo viên trong trường.

-- Trigger 18: Một giáo viên chỉ quản lý tối đa 3 giáo viên khác.
CREATE OR ALTER TRIGGER tg_23120264_R18
ON GIAOVIEN
FOR INSERT, UPDATE
AS
IF UPDATE(GVQLCM)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN GIAOVIEN GV ON I.GVQLCM = GV.GVQLCM
        GROUP BY GV.GVQLCM
        HAVING COUNT(GV.MAGV) > 3
    )
    BEGIN
        RAISERROR (N'GIAO VIEN CHI QUAN LY TOI DA 3 GIAO VIEN KHAC', 16, 1)
        ROLLBACK
    END;
END;
GO

-- Trigger 19: Giáo viên chỉ tham gia những đề tài mà giáo viên chủ nhiệm đề tài là người cùng bộ môn với giáo viên đó.
CREATE OR ALTER TRIGGER tg_23120264_R19
ON THAMGIADT
FOR INSERT, UPDATE
AS
IF UPDATE(MAGV) OR UPDATE(MADT)
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED I
        JOIN GIAOVIEN GV ON I.MAGV = GV.MAGV
        JOIN DETAI DT ON I.MADT = DT.MADT
        JOIN GIAOVIEN GVCN ON DT.GVCNDT = GVCN.MAGV
        WHERE GV.MaBM != GVCN.MaBM
    )
    BEGIN
        RAISERROR (N'GIAO VIEN CHI THAM GIA DE TAI CUNG BO MON VOI GVCN', 16, 1)
        ROLLBACK
    END;
END