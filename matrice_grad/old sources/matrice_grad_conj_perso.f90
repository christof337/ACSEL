program yolo
	! compilation et lien: gfortran -O matrice_grad_conj_perso.f90 -o matrice_grad_conj_perso.exe

	! ce code est inspiré du programme "matricegrad".

	! l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 

	!integer,parameter :: p4 = selected_real_kind(6) 	!4
	!integer,parameter :: p8 = selected_real_kind(15)	!8
	!integer,parameter :: p10 = selected_real_kind(16)	!10
	!integer,parameter :: p16 = selected_real_kind(33)	!16
	
	integer, parameter :: P = 8 ! faire varier
	
	real(kind=selected_real_kind(P)), allocatable, dimension(:):: x,xx,b
	real(kind=selected_real_kind(P)), allocatable, dimension(:,:):: a
	real(kind=selected_real_kind(P)), allocatable, dimension(:):: gk,agk,dk,adk
	real(kind=selected_real_kind(P)), allocatable, dimension(:):: solg,solgc
	
	character(len=1024) :: filename
	
	print *,'Taille matrice ?'
	read(5,*) N
	
	!real(kind=l), allocatable, dimension(:):: x,xx,b
	!real(kind=l), allocatable, dimension(:,:):: a
	!real(kind=l), allocatable, dimension(:):: gk,agk,dk,adk
	!real(kind=l), allocatable, dimension(:):: solg,solgc

	allocate(x(N))
	allocate(xx(N))
	allocate(b(N))
	allocate(a(N,N))
	allocate(gk(N))
	allocate(agk(N))
	allocate(dk(N))
	allocate(adk(N))
	allocate(solg(N))
	allocate(solgc(N))

	igc=1  ! gradient ou gradient conjugue
	nbgrad=30 ! nbre iterations gradient

	b(1:N)=0
	
	open(1,file='matrix.dat',status='unknown')
	do i=1,N
		x(i)=i
		do j=1,N
			a(i,j)=exp(-0.05*(i-j)**2)
			write(1,*) i,j,a(i,j)
		enddo
		write(1,'()')
	enddo
	close(1)

	! visualisation de matrix.dat avec gnuplot
	! splot 'matrix.dat' w l 

	b=matmul(a,x)  !cible

	!
	!inversion par minimisation d'energie
	! methode de gradient a x = b , il faut retrouver x
	!
	! initialisation

	xx(1:N)=0

	if(igc.eq.0) then

		do 1 iter=1,nbgrad

			!gk=matmul(a,xx)-b 
			
			do i=1,N
				gk(i)=0
				do j=1,N
					gk(i)=gk(i)+a(i,j)*xx(j)
				enddo
				gk(i)=gk(i)-b(i)
			enddo

			!agk=matmul(a,gk)

			do i=1,N
				agk(i)=0
				do j=1,N
					agk(i)=agk(i)+a(i,j)*gk(j)
				enddo
			enddo


			!gkgk=dot_product(gk,gk)
			!agkgk=dot_product(agk,gk)

			gkgk=0
			agkgk=0
			do i=1,N
				gkgk=gkgk+gk(i)**2
				agkgk=agkgk+agk(i)*gk(i)
			enddo

			alphak=gkgk/agkgk

			! xx(1:N)=xx(1:N)-alphak*gk(1:N)

			do i=1,N
				xx(i)=xx(i)-alphak*gk(i)
			enddo

			print *,iter,gkgk
			
			1 continue  !nbgrad

			solg(1:N)=xx(1:N)


	endif ! igc=0


		if(igc.eq.1) then ! gradient conjugue

			xx(1:N)=0
			gk=matmul(a,xx)-b
			dk(1:N)=gk(1:N)   

			do 2 iter=1,nbgrad
				
				adk=matmul(a,dk)
				gkgk=dot_product(gk,gk)
				adkdk=dot_product(adk,dk)
				alphak=gkgk/adkdk
				xx(1:N)=xx(1:N)-alphak*dk(1:N)
				gk(1:N)=gk(1:N)-alphak*adk(1:N) 
				
				gkgk2=0
				do i=1,N
					gkgk2=gkgk2+gk(i)**2
				enddo
				gkgk2=sqrt(gkgk2);
				
				gk1gk1=dot_product(gk,gk)    
				betak1=gk1gk1/gkgk
				dk(1:N)=gk(1:N)+betak1*dk(1:N)

				print *,iter,gkgk
				! write(77,*) iter,gkgk2

				2 continue

				solgc(1:N)=xx(1:N)
				
			endif !igc=1

			
			do i=1,N9
				print *,x(i),solgc(i)
			enddo
			
			
			! visu gnuplot :  plot 'sol_ggc16.dat' w l,'sol_ggc16.dat' u 1:3 w l,'sol_ggc16.dat' u 1:4 w l

			write (filename, "(A7,I2,A4)") "sol_ggc", P, ".dat"
			open(1,file=filename,status='unknown')
			do i=1,N
				write(1,*) i,x(i),solgc(i)
			enddo
			close(1)

			print *, "plot 'sol_ggc",P,".dat' u 1:4 w l"

			deallocate(x)
			deallocate(xx)
			deallocate(b)
			deallocate(a)
			deallocate(gk)
			deallocate(agk)
			deallocate(dk)
			deallocate(adk)
			deallocate(solg)
			deallocate(solgc)

			print *,'fin normal'   
		end