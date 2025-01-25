import cv2
import numpy as np

target_ral_code = None
target_rgb = None

with open("ral_codes.txt", "r") as f:
  target_ral_code = f.readline().strip()
  # Read the RGB line
  rgb_line = f.readline().strip()
  # Check if the RGB line is empty
  if rgb_line:
      # Split on commas and convert to integers
      rgb_values_str = rgb_line.split(",")
      target_rgb = [int(x) for x in rgb_values_str]
  else:
      # Handle empty line (e.g., raise an exception or set default values)
      raise ValueError("Empty line in RGB values file")

cap = cv2.VideoCapture(0)

while True:
  ret, frame = cap.read()

if not ret:
    print("Kamera hatası!")
    break

  # Görüntüyü HSV renk uzayına dönüştür
  hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

  lower_bound = np.array([0, 50, 50])
  upper_bound = np.array([179, 255, 255])

  mask = cv2.inRange(hsv_frame, lower_bound, upper_bound)

  result = cv2.bitwise_and(frame, frame, mask=mask)

  # Kontur bulma
  contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

  if contours:
    max_contour = max(contours, key=cv2.contourArea)

    x, y, w, h = cv2.boundingRect(max_contour)

    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

  while True:
    center_x, center_y = x + w // 2, y + h // 2
    pixel_color = frame[center_y, center_x]

    # Hedef nesnenin rengiyle hedef RAL renginin RGB değerleri arasındaki farkı hesaplama
    color_difference = np.linalg.norm(np.array(pixel_color) - np.array(target_rgb))

    if color_difference > 10:  
      Continue

    cv2.putText(frame, f"Renk Farkı: {color_difference:.2f}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    break

  cv2.imshow('Frame', frame)
  key = cv2.waitKey(1) & 0xFF

  if key == ord('q'):
    break

cap.release()
cv2.destroyAllWindows()
