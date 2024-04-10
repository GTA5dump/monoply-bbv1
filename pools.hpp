namespace rage {
	class PoolUtils
	{
	public:
		inline auto to_array()
		{
			std::vector<Entity> arr;
			for (auto entity : *static_cast<T*>(this))
			{
				arr.push_back(patterns::ptr_to_handle(entity));
			}

			return arr;
		}

		auto begin()
		{
			return ++pool_iterator<T>(static_cast<T*>(this), -1);
		}

		auto end()
		{
			return ++pool_iterator<T>(static_cast<T*>(this), static_cast<T*>(this)->m_size);
		}
	};
class GenericPool : public PoolUtils<GenericPool>
{
public:
	UINT64 m_pool_address;
	BYTE* m_bit_array;
	UINT32 m_size;
	UINT32 m_item_size;

	inline bool is_valid(UINT32 i)
	{
		return mask(i) != 0;
	}

	inline UINT64 get_address(UINT32 i)
	{
		return mask(i) & (m_pool_address + i * m_item_size);
	}

private:
	inline long long mask(UINT32 i)
	{
		long long num1 = m_bit_array[i] & 0x80;
		return ~((num1 | -num1) >> 63);
	}
};