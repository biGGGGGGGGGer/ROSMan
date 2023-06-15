
(cl:in-package :asdf)

(defsystem "speedimu-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "imuspeed" :depends-on ("_package_imuspeed"))
    (:file "_package_imuspeed" :depends-on ("_package"))
  ))