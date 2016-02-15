/// \file interstpoint.h
/// \brief Interest Point
///
/// \author C. Andre (c.andre@apeira-technologies.fr)
/// \version 1.0
/// \date September 2015
///
/// This code was developped by Apeira Technologies
/// Contact: m.voiry@apeira-technologies.fr

#ifndef CORE_INTEREST_POINT_H
#define CORE_INTEREST_POINT_H

#include "typedef.h"

namespace core
{
	/// \brief Descriptor of a point
	template<typename T = float_t,int32 I = 64>
	class Descriptor;

	/// \brief InterstPoint
	template<typename T = float_t, int32 I = 64>
	struct InterestPoint;

	/// \brief Vector of interst points
	template<typename T = float_t, int32 I = 64>
	class InterestPointVector :
		public std::vector<InterestPoint<T, I> >
	{
	public:
		typedef InterestPoint<T, I> value_type;

		enum
		{
			n_descriptors = I
		};
	};

	template<typename T = float_t, int32 I = 64>
	class InterestPair:
		public std::vector<std::pair<InterestPoint<T, I>,
								InterestPoint<T, I> > >
	{
	public:
		typedef T value_type;
		enum
		{
			n_descriptors = I
		};
	};

	// Descriptor of a point
	template <typename T,int32 I>
	class Descriptor
	{
	private:
		T data_[I];
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T value_type;
		/// \brief Default constructor
		Descriptor(){}

		/// \brief Constructor with pointer
		Descriptor(const T* data)
		{
			assign(data);
		}
		/// \brief Constructor with iterator
		template <class InputIterator>
		Descriptor(InputIterator first)
		{
			assign(first);
		}

		/// \brief Copy constructor
		Descriptor(const Descriptor& x)
		{
			assign(x.begin());
		}

		/// \brief Constructor with il
		Descriptor(std::initializer_list<T> il)
		{
			assign(il);
		}

		/// \brief Initialization with pointer
		void assign(const T* data)
		{
			memcpy(data_, data, sizeof(T)*I);
		}
		/// \brief Initialization with iterator
		template <class InputIterator>
		void assign(InputIterator first)
		{
			for (uint32 i = 0; i < I; ++i)
				data_[i] = *first++;
		}

		/// \brief Initialization with value
		void assign(const T& val)
		{
			for (uint32 i = 0; i < I; ++i)
				data_[i] = val;
		}
		void assign()
		{
			assign(T());
		}
		/// \brief Initialization with initializer list
		void assign(std::initializer_list<value_type> il)
		{
			auto it = il.begin();
			for (uint32 i = 0; i < I; ++i)
				data_[i] = *it++;
		}


		/// \brief Access to data pointer
		const T* data()const
		{
			return data_;
		}
		/// \brief Random access operator
		T& operator[](uint32 i)
		{
			assert(i < I);
			return data_[i];
		}
		/// \brief Const random access operator
		const T& operator[](uint32 i)const
		{
			assert(i < I);
			return data_[i];
		}

		/// \brief Random access function
		T& at(uint32 i)
		{
			return data_[i];
		}
		const T& at(uint32 i)const
		{
			return data_[i];
		}

		uint32 size()const
		{
			return I;
		}
		/// \brief Iterator referring to the first element
		iterator begin()
		{
			return data_;
		}
		const_iterator begin()const
		{
			return data_;
		}

		/// \brief Iterator referring to the past the end element
		iterator end()
		{
			return data_ + I;
		}
		const_iterator end()const
		{
			return data_ + I;
		}
	};

	// Interst point
	template<typename T,int32 I>
	struct InterestPoint
	{
		enum
		{
			n_descriptors = I,
		};
		typedef T value_type;
		typedef Descriptor<T, I> descriptor_t;

		// Int position
		uint32 octave;
		uint32 interval;
		uint32 ix, iy;
		// Coordinates
		float_t x, y;
		// Displacement
		float_t dx, dy;
		// Scale
		float_t scale;
		// Orientation
		float_t orientation;
		// Sign of laplacian
		int32 laplacian;
		// Descriptor
		descriptor_t descriptor;
		//Default constructor
		InterestPoint(){}
		//init
		void init(uint32 new_o, uint32 new_i,
			uint32 new_ix, uint32 new_iy, ...)
		{
			octave = new_o;
			interval = new_i;
			ix = new_ix;
			iy = new_iy;
		}
		void set_interp_value
			(const float_t& new_x,
			const float_t& new_y,
			const float_t& new_scale,
			int32 new_laplacian)
		{
			x = new_x;
			y = new_y;
			scale = new_scale;
			laplacian = new_laplacian;
		}

		//Const random access operator to descriptor
		const T& operator[](uint32 i)const
		{
			assert(i < I);
			return descriptor[i];
		}
		// Random access operator to descriptor
		T& operator[](uint32 i)
		{
			assert(i < I);
			return descriptor[i];
		}
		// Descriptor size
		uint32 size()const
		{
			return I;
		}
	};

	template<typename T, int32 I>
	inline T distance(const InterestPoint<T, I>& pt1,
		const InterestPoint<T, I>& pt2)
	{
		T sum = 0;
		for (uint32 i = 0; i < I; ++i)
		{
			T tmp = (pt1.descriptor[i] - pt2.descriptor[i]);
			sum += tmp * tmp;
		}
		return sqrt(sum);
	}
	//Matching
	template<typename T, int32 I>
	void Matching
		(InterestPointVector<T, I>& ipts1,
		InterestPointVector<T, I>& ipts2,
		InterestPair<T, I>& matches, T thresh = 0.65f,float_t dist_max = -1)
	{
		T dist, d1, d2;
		if (dist_max > 0)
			dist_max = dist_max * dist_max;
		else
			dist_max = Limit<float_t>::greatest();
		//Initialisation
		const size_t n_pts1 = ipts1.size();
		const size_t n_pts2 = ipts2.size();
		matches.clear();
		//Boucle sur ipts1
		for (size_t i = 0; i < n_pts1; ++i)
		{
			d1 = d2 = Limit<float_t>::greatest();
			uint32 indj = -1;
			auto& pt1 = ipts1[i];
			//Boucle sur ipts2
			for (size_t j = 0; j < n_pts2; ++j)
			{
				auto& pt2 = ipts2[j];
				float_t dx = pt1.x - pt2.x;
				float_t dy = pt2.y - pt2.y;
				float_t d = dx * dx + dy * dy;
				if (d < dist_max)
				{
					dist = distance(pt1, pt2);
					if (dist<d1)
					{
						d2 = d1;
						d1 = dist;
						indj = j;
					}
					else if (dist<d2)
					{
						d2 = dist;
					}
				}
			}
			if (d1 < thresh * d2 && indj < n_pts2)
			{
				// Store the change in position
				auto& pt2 = ipts2[indj];
				pt1.dx = pt2.x - pt1.x;
				pt1.dy = pt2.y - pt1.y;
				pt2.dx = -pt1.dx;
				pt2.dy = -pt1.dy;
				matches.push_back(std::make_pair(pt1,pt2));
			}
		}
	}
} // core

#endif
