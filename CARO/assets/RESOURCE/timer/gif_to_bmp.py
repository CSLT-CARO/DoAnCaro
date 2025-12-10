from PIL import Image
import os
import sys

def extract_gif_frames_to_bmp(gif_path):
    """
    Tách tất cả các frame của tệp GIF thành các tệp BMP riêng biệt.

    Args:
        gif_path (str): Đường dẫn đến tệp GIF.
    """
    try:
        # 1. Mở tệp GIF
        img = Image.open(gif_path)
    except FileNotFoundError:
        print(f"LỖI: Không tìm thấy tệp '{gif_path}'. Vui lòng kiểm tra lại tên file và đường dẫn.")
        return
    except Exception as e:
        print(f"LỖI: Không thể mở tệp GIF. Lỗi: {e}")
        return

    # 2. Chuẩn bị biến đếm
    frame_count = 0

    print(f"Bắt đầu xử lý tệp: {gif_path}")

    # 3. Lặp qua các frame
    while True:
        try:
            # DÒNG NÀY ĐÃ ĐƯỢC CẬP NHẬT:
            # frame_filename sẽ là "timer_0.bmp", "timer_1.bmp", ...
            frame_filename = f"timer_{frame_count}.bmp"
            
            # Đảm bảo mỗi frame được chuyển đổi sang chế độ RGB
            frame_to_save = img.convert("RGB")
            
            # Lưu frame dưới định dạng BMP
            frame_to_save.save(frame_filename, 'BMP')
            
            print(f"Đã lưu: {frame_filename}")
            
            frame_count += 1
            
            # Chuyển sang frame tiếp theo. 
            img.seek(frame_count) 
            
        except EOFError:
            # Đã đạt đến cuối tệp GIF
            break
        except Exception as e:
            print(f"LỖI trong quá trình xử lý frame {frame_count}: {e}")
            break

    print("-" * 30)
    print(f"Hoàn tất! Đã trích xuất {frame_count} frame thành tệp BMP.")
    

if __name__ == "__main__":
    if len(sys.argv) < 2:
        GIF_FILE = "Transaction_animation.gif" 
        print(f"⚠️ Không có tên file được cung cấp. Sử dụng tên mặc định: {GIF_FILE}")
        extract_gif_frames_to_bmp(GIF_FILE)
    else:
        GIF_FILE = sys.argv[1]
        extract_gif_frames_to_bmp(GIF_FILE)