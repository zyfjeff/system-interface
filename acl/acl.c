#include <stdio.h>


/*
 *  mount -o acl 选项开启acl支持
 *  acl未形成标准化,因此如果运用了ACL技术,就会危及到应用的可移植性
 *
 *  ACL记录,一个ACL是由一系列的ACL记录(简称ACE)组成:
 *
 *  ACE(由3个部分组成):
 *      标记类型    表示该记录作用于一个用户,组,还是其他类别的用户
 *      标记限定符  标识特定的用户或组
 *      权限集合    本字段包含所授予的权限信息
 *  标记类型取值:
 *      ACL_USER_OBJ
 *          授予文件属主的权限(每个ACL只能包含一条),对应于传统的文件属主权限
 *      ACL_USER
 *          授予某用户的权限,一个ACL可以包含零个或多个此类型的记录,对于一个特定用户最多只能定义一条
 *      ACL_GROUP_OBJ
 *          记录了授予文件组的权限(每个ACL只能一条),对应于传统的文件属组权限
 *      ACL_MASK
 *          记录了可由ACL_USER ACL_GROUP_OBJ,ACL_GROUP_OBJ型ACE所能授予的最高权限
 *      ACL_OTHER
 *          对于不匹配任何其他ACE的用户,由包含该值的ACE授予权限,只能包含一条,对应于传统文件的other用户权限
 *
 *  最小ACL和扩展ACL
 *      最小化ACL语义上等同于传统的文件权限集合,恰好由3条记录组成,每条标记的类型分别为ACL_USER_OBJ,ACL_GROUP_OBJ以及ACL_OTHER
 *      扩展ACL则是除此之外,还包含标记类型为ACL_USER,ACL_GROUP ACL_MASK的记录
 *
 * ACL权限检查算法:
 *
 *  ACL_USER_OBJ
 *  ACL_USER
 *  ACL_GROUP_OBJ
 *  ACL_GROUP
 *  ACL_OTHER
 *
 *
 * 通过getfacl可以获取一个文件的acl属性的ACE记录,记录会按照如下格式输出:
 * tag-type:[tag-qualifier]:permissions
 *
 * 对于上面提到的标记类型,都有一个标记的文本格式
 * user    == ACL_USER_OBJ
 * u       == ACL_USER
 * g,group == ACL_GROUP_OBJ
 * g       == ACL_GROUP
 * m       == ACL_MASK
 * other   == ACL_OTHER
 *
 * 下面是一个文件的acl
 *  user::rw-
 *  group::r--
 *  other::r--
 *  这个文件包含了三条ACE记录,分别是ACL_USER_OBJ ACL_GROUP_OBJ ACL_OTHER 分别对应于传统文件的属主,属组,和other
 *
 *
 *  setfacl -m [u|g]:[name]:[rwx] file 设置ACL_USER ACL_GROUP
 *  setfacl -R 递归设置
 *  setfacl -x [u:g][name] file 删除ACL_USER ACL_GROUP 可以有多个，逗号分割即可
 *  setfacl -b 删除所有的扩展ACE条目,保留最小化的ACE
 *
 *  getfacl 查看acl规则 --omit-header 略去开头的注释信息
 *
 *  访问型ACL   判定进程对文件的访问权限
 *  默认型ACL   决定了目录下所创建文件或子目录的ACL和权限
 *
 *  setfacl getfacl 通过-d选项来设置默认型ACL
 *      设置了默认型ACL后，该目录下的子目录继承其默认型ACL,该目录下的子文件会将其默认型ACL当做访问型ACL继承
 *      -k 可删除默认型ACL
 */


