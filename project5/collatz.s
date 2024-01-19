 #Zachary Meyers
 # UID 120279096
 # zmeyers3 
 
collatz:
   # PROLOGUE
   subu	$sp, $sp, 8
   sw	$ra, 8($sp)
   sw	$fp, 4($sp)
   addu	$fp, $sp, 8

   # BODY
   lw $t1, 12($sp) # load n from stack
   lw $t2, 16($sp) # load d from stack

   move $v0, $t2 # store d in return value

   beq $t1, 1, exit

   rem $t3, $t1, 2
   beqz $t3, even # go to even part of the function

   mul $t1, $t1, 3 # multiply n * 3
   addi $t1, $t1, 1 # compute (3 * n) + 1
   addi $t2, $t2, 1 # compute d + 1
   
   subu $sp, $sp, 8 # create space on stack for s1 and s2
   sw $t1, 4($sp) # store n 
   sw $t2, 8($sp) # store d

   jal collatz
   j exit

even:
   srl $t1, $t1, 1 # divide n / 2
   addi $t2, $t2, 1 # compute d + 1

   subu $sp, $sp, 8 # create space on stack for s1 and s2
   sw $t1, 4($sp) # store n 
   sw $t2, 8($sp) # store d

   jal collatz
   j exit

exit:
   move $sp, $fp
   lw	$ra, ($fp)
   lw	$fp, -4($sp)
   jr	$ra



   








