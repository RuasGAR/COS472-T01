program main
    use ISO_FORTRAN_ENV
  
    implicit none
    
    integer, parameter :: n_max = 18000
    
    real(kind=8), dimension(:), allocatable :: x, b
    real(kind=8), dimension(:,:), allocatable :: matrix
    integer :: i, cur_size, nums(5) = [2000, 4000, 8000, 16000, n_max]
    real :: t_start, t_end, exe_time
    real(kind=8) acc
    integer :: f
  
    call srand(time())
    
    open(unit=f,file="../../experiments/matrix_row_column_xp_FORTRAN.txt",status="NEW")
    
    write(f,*)
    
    do i = 1, size(nums)
        
        cur_size = nums(i)
        
        allocate(matrix(cur_size,cur_size))
        allocate(x(cur_size))
        allocate(b(cur_size))
        
        call fill_matrix(matrix, cur_size)
        call fill_vector(x, cur_size)
        call fill_vector(b, cur_size)
        
        call cpu_time(t_start)
        call matrix_mult(matrix, x, b, cur_size)
        call cpu_time(t_end)
        exe_time = t_end - t_start
        
        deallocate(matrix)
        deallocate(x)
        deallocate(b)
        
        write(f,"(I0,A,F8.6)") cur_size,";",exe_time
        
    end do
    
    close(unit=f)
    
  contains
    
    subroutine fill_vector(vec_ptr, size)
        real(kind=8), dimension(:), intent(out) :: vec_ptr
        integer, intent(in) :: size
        integer :: i
        
        do i = 1, size
            call random_number(vec_ptr(i))
        end do
        
    end subroutine
    
    
    subroutine fill_matrix(matrix_ptr, size)
        real(kind=8), dimension(:,:), intent(out) :: matrix_ptr
        integer, intent(in) :: size
        integer :: i, j
        
        do i = 1, size
            do j = 1, size
                call random_number(matrix_ptr(i,j))
            end do
        end do
        
    end subroutine
    
    
    subroutine matrix_mult(matrix_ptr, x_ptr, b_ptr, size)
        real(kind=8), dimension(:,:), intent(in) :: matrix_ptr
        real(kind=8), dimension(:), intent(in) :: x_ptr
        real(kind=8), dimension(:), intent(out) :: b_ptr
        integer, intent(in) :: size
        integer :: i, j
        
        do i = 1, size
            acc = 0
            do j = 1, size
                acc = acc + matrix_ptr(i,j) * x_ptr(j)
            end do
            b_ptr(i) = acc
        end do
        
    end subroutine
    
end program
  