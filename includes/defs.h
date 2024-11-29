/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:22:43 by bama              #+#    #+#             */
/*   Updated: 2024/11/29 15:30:56 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define DEFAULT_TERM "xterm-256color"
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin"
# define LSCOLORS "Gxfxcxdxbxegedabagacad"
# define LS_COLORS "rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=\
01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;4\
2:ow=34;42:st=37;44:ex=01;32:*=00;93:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.\
taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01\
;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=0\
1;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.b\
z=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31\
:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=\
01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.\
dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpe\
g=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35\
:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svg\
z=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;3\
5:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.m\
p4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35\
:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=0\
1;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.\
ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00\
;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.og\
a=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.c\
rdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=\
00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmori\
g=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;9\
0:*.ucf-old=00;90:"

# define TAB_SIZE	4

# define BOOL char

# define JOKER_NO		-1
# define JOKER_YES		0
# define JOKER_SINGLE	1

# define HEREDOC_PROMPT "HereDoc $> "

# define PROMPT1 "\e[1m\e[38;2;0;165;140m"
# define PROMPT1_SIZE 9

# define PROMPT1BIS "\e[1m\e[38;2;188;148;195m"
# define PROMPT1BIS_SIZE 9

# define PROMPT2 " $> "
# define PROMPT2_SIZE 4

# define PROMPT3 "\e[0m"
# define PROMPT3_SIZE 4

# define EXIT_TEXT "\e[31m\n\nexit\n\e[0m"
# define EXIT_TEXT_SIZE 15

# ifndef ARG_MAX
#  define ARG_MAX 2087151
# endif

# define CWD_MAX_LEN 25
# define CWD_AT_NAME "@"

// ARG_MAX / 2
# define SZ_MAX 1174302

# define EXEC_BIN	-1
# define ECHO_BLT	1
# define UNSET_BLT	2
# define CD_BLT		3
# define EXIT_BLT	4
# define EXPORT_BLT	5
# define ENV_BLT	6
# define PWD_BLT	7
# define HDEL_BLT	8

# define FORKED		1

# define F_UNKNOWN	0
# define DIRECTORY	4
# define REG_FILE	8

# define KEY_DEL	"\033[3~"
# define KEY_T_UP	"\033[A"
# define KEY_DOWN	"\033[B"
# define KEY_RIGHT	"\033[C"
# define KEY_LEFT	"\033[D"

# define T_UP 65
# define DOWN 66
# define RIGHT 67
# define LEFT 68

# define READ 16
# define S_CHUNK 256
# define B_CHUNK 1024
# define TERM 4096

# define NB_OF_PROC_MAX_PER_USER 1023

# define CANON 0
# define RAW 1

# define HISTORY_PATH "/.miniflop_history"

# define CTRL_L	0x0C

#endif