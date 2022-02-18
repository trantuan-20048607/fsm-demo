/**
 * Self tag for C++.
 * \author trantuan-20048607
 * \date 2022.1.20
 * \details Introduced from ruby and python, self tag is used to replace ugly *this
 *   to refer to object itself.
 */

#ifndef _LANG_FEATURE_EXTENSION__SELF_TAG_H_
#define _LANG_FEATURE_EXTENSION__SELF_TAG_H_

/**
 * \brief __SELF__ represents for C++ object itself (simply defined as *this),
 *   corresponding "self" in ruby and python.
 */
#define __SELF__ *this

#endif  // _LANG_FEATURE_EXTENSION__SELF_TAG_H_
