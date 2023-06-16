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
  :slots (_a ))

(defmethod speedimu::imuspeed
  (:init
   (&key
    ((:a __a) 0.0)
    )
   (send-super :init)
   (setq _a (float __a))
   self)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:serialization-length
   ()
   (+
    ;; float32 _a
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _a
       (sys::poke _a (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _a
     (setq _a (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get speedimu::imuspeed :md5sum-) "3a9a8ccf1ae2be3477477819c0d93b4e")
(setf (get speedimu::imuspeed :datatype-) "speedimu/imuspeed")
(setf (get speedimu::imuspeed :definition-)
      "float32 a




")



(provide :speedimu/imuspeed "3a9a8ccf1ae2be3477477819c0d93b4e")


