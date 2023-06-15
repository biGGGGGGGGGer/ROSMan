;; Auto-generated. Do not edit!


(when (boundp 'speedimu::imuspeed)
  (if (not (find-package "SPEEDIMU"))
    (make-package "SPEEDIMU"))
  (shadow 'imuspeed (find-package "SPEEDIMU")))
(unless (find-package "SPEEDIMU::IMUSPEED")
  (make-package "SPEEDIMU::IMUSPEED"))

(in-package "ROS")
;;//! \htmlinclude imuspeed.msg.html


(defclass speedimu::imuspeed
  :super ros::object
  :slots (_pitch _roll _yaw ))

(defmethod speedimu::imuspeed
  (:init
   (&key
    ((:pitch __pitch) 0.0)
    ((:roll __roll) 0.0)
    ((:yaw __yaw) 0.0)
    )
   (send-super :init)
   (setq _pitch (float __pitch))
   (setq _roll (float __roll))
   (setq _yaw (float __yaw))
   self)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:serialization-length
   ()
   (+
    ;; float32 _pitch
    4
    ;; float32 _roll
    4
    ;; float32 _yaw
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _pitch
     (setq _pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _roll
     (setq _roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get speedimu::imuspeed :md5sum-) "5cdafae0cb68983e8e8825adb0b735f2")
(setf (get speedimu::imuspeed :datatype-) "speedimu/imuspeed")
(setf (get speedimu::imuspeed :definition-)
      "float32 pitch
float32 roll
float32 yaw
")



(provide :speedimu/imuspeed "5cdafae0cb68983e8e8825adb0b735f2")


