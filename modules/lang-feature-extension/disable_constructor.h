/**
 * A quick tool to disable redundant constructors.
 * \author trantuan-20048607
 * \date 2022.2.18
 * \details Use constructor disabling tag as one of parent classes.
 */

#ifndef _LANG_FEATURE_EXTENSION__DISABLE_CONSTRUCTOR_H_
#define _LANG_FEATURE_EXTENSION__DISABLE_CONSTRUCTOR_H_

namespace disable_constructor {
    class DisableMoveConstructor {
    public:
        DisableMoveConstructor() = default;

        ~DisableMoveConstructor() = default;

        DisableMoveConstructor(DisableMoveConstructor &&) = delete;

        DisableMoveConstructor &operator=(DisableMoveConstructor &&) = delete;
    };

    class DisableCopyConstructor {
    public:
        DisableCopyConstructor() = default;

        ~DisableCopyConstructor() = default;

        DisableCopyConstructor(const DisableCopyConstructor &) = delete;

        DisableCopyConstructor &operator=(const DisableCopyConstructor &) = delete;
    };
}

/**
 * \brief Move constructor disabler.
 * \details Use this tag like a normal class to inherit:
 * \code
 *   class Foo : NO_MOVE {
 *     ...
 *   };
 * \endcode
 */
#define NO_MOVE public disable_constructor::DisableMoveConstructor

/**
 * \brief Copy constructor disabler.
 * \details Use this tag like a normal class to inherit:
 * \code
 *   class Foo : NO_COPY {
 *     ...
 *   };
 * \endcode
 */
#define NO_COPY public disable_constructor::DisableCopyConstructor

#endif  // _LANG_FEATURE_EXTENSION__DISABLE_CONSTRUCTOR_H_
