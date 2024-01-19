 #Zachary Meyers
 # UID 120279096
 # zmeyers3 
 
    .text

strlen:
   # PROLOGUE
   subu	$sp, $sp, 8
   sw	$ra, 8($sp)
   sw	$fp, 4($sp)
   addu	$fp, $sp, 8

   # BODY
   li $v0, 0 # initialize counter to 0
   move $t9, $a0 # store word in another temp

   loop:
      lb $t0, 0($t9) # load first character of word
      beqz $t0, end # if next character is null byte, end
      addu $v0, $v0, 1 # increment len counter by 1
      addu $t9, $t9, 1 # increment word pointer by 1 character
      j loop # repeat loop until exit


   # EPILOGUE
   end:
    move	$sp, $fp
    lw	$ra, ($fp)
    lw	$fp, -4($sp)
    jr	$ra

is_palindrome:

   # PROLOGUE
   subu	$sp, $sp, 8
   sw	$ra, 8($sp)
   sw	$fp, 4($sp)
   addu	$fp, $sp, 8

   # BODY
   li $v0, 0
   jal strlen # initialize with string length
   move $t0, $v0 # store strlen in $t0

   li $t1, 0 # initialize start index variable
   subu $t2, $t0, 1 # initialize end index variable
   addu $a1, $a0, $t2 # set a1 to point to last index

   li $v0, 1 # $v0 is true until proven false
   loop2:
      bgt $t1, $t2, exit # end loop if start index bigger than end
      lb $t3, 0($a0) # load character at index $t1
      lb $t4, 0($a1) # load character at index $t2
      bne $t3, $t4, failed # if characters aren't equal, return failed
      
      addu $t1, $t1, 1 # increment start index
      subu $t2, $t2, 1 # decrement end value
      addu $a0, $a0, 1 # increment start pointer
      subu $a1, $a1, 1 # decrement end pointer
      j loop2 # repeat loop until exit

   failed:
      li $v0, 0 # if not a palindrome, set $v0 to 0
      j exit

   # EPILOGUE
   exit:
     move	$sp, $fp
     lw	$ra, ($fp)
     lw	$fp, -4($sp)
     jr	$ra



   








