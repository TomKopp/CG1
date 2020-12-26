


	case TI_INT8+UTO_VEC : 
		{
			const vec<int8_type>& v = *static_cast<const vec<int8_type>*>(value_ptr);
			if (dimension_independent) {

				vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT16+UTO_VEC : 
		{
			const vec<int16_type>& v = *static_cast<const vec<int16_type>*>(value_ptr);
			if (dimension_independent) {

				vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT32+UTO_VEC : 
		{
			const vec<int32_type>& v = *static_cast<const vec<int32_type>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, v[0], v[1]); break;
				case 3 : glUniform3i(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4i(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1iv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_UINT8+UTO_VEC : 
		{
			const vec<uint8_type>& v = *static_cast<const vec<uint8_type>*>(value_ptr);
			if (dimension_independent) {

				vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT16+UTO_VEC : 
		{
			const vec<uint16_type>& v = *static_cast<const vec<uint16_type>*>(value_ptr);
			if (dimension_independent) {

				vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { vec<int32_type> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT32+UTO_VEC : 
		{
			const vec<uint32_type>& v = *static_cast<const vec<uint32_type>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0]));
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0])); break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_VEC : 
		{
			const vec<flt32_type>& v = *static_cast<const vec<flt32_type>*>(value_ptr);
			if (dimension_independent) {

				glUniform1fv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, v[0], v[1]); break;
				case 3 : glUniform3f(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4f(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1fv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_FLT64+UTO_VEC : 
		{
			const vec<flt64_type>& v = *static_cast<const vec<flt64_type>*>(value_ptr);
			if (dimension_independent) {

				vec<flt32_type> vi = v; glUniform1fv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, (flt32_type)v[0], (flt32_type)v[1]); break;
				case 3 : glUniform3f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2]); break;
				case 4 : glUniform4f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2], (flt32_type)v[3]); break;

				default: { vec<flt32_type> vi = v; glUniform1fv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_MAT:
		{
			const mat<flt32_type>& m = *static_cast<const mat<flt32_type>*>(value_ptr);
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}
	case TI_FLT64+UTO_MAT:
		{
			const mat<flt64_type>& md = *static_cast<const mat<flt32_type>*>(value_ptr);
			mat<flt32_type> m = md;
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}

	case TI_INT8+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<int8_type,2>& v = *static_cast<const fvec<int8_type,2>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT16+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<int16_type,2>& v = *static_cast<const fvec<int16_type,2>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT32+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<int32_type,2>& v = *static_cast<const fvec<int32_type,2>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, v[0], v[1]); break;
				case 3 : glUniform3i(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4i(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1iv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_UINT8+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<uint8_type,2>& v = *static_cast<const fvec<uint8_type,2>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT16+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<uint16_type,2>& v = *static_cast<const fvec<uint16_type,2>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,2> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT32+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<uint32_type,2>& v = *static_cast<const fvec<uint32_type,2>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0]));
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0])); break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<flt32_type,2>& v = *static_cast<const fvec<flt32_type,2>*>(value_ptr);
			if (dimension_independent) {

				glUniform1fv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, v[0], v[1]); break;
				case 3 : glUniform3f(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4f(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1fv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_FLT64+UTO_FVEC + (2 - 2)*UTO_DIV : 
		{
			const fvec<flt64_type,2>& v = *static_cast<const fvec<flt64_type,2>*>(value_ptr);
			if (dimension_independent) {

				fvec<flt32_type,2> vi = v; glUniform1fv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, (flt32_type)v[0], (flt32_type)v[1]); break;
				case 3 : glUniform3f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2]); break;
				case 4 : glUniform4f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2], (flt32_type)v[3]); break;

				default: { fvec<flt32_type,2> vi = v; glUniform1fv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT8+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<int8_type,3>& v = *static_cast<const fvec<int8_type,3>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT16+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<int16_type,3>& v = *static_cast<const fvec<int16_type,3>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT32+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<int32_type,3>& v = *static_cast<const fvec<int32_type,3>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, v[0], v[1]); break;
				case 3 : glUniform3i(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4i(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1iv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_UINT8+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<uint8_type,3>& v = *static_cast<const fvec<uint8_type,3>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT16+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<uint16_type,3>& v = *static_cast<const fvec<uint16_type,3>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,3> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT32+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<uint32_type,3>& v = *static_cast<const fvec<uint32_type,3>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0]));
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0])); break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<flt32_type,3>& v = *static_cast<const fvec<flt32_type,3>*>(value_ptr);
			if (dimension_independent) {

				glUniform1fv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, v[0], v[1]); break;
				case 3 : glUniform3f(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4f(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1fv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_FLT64+UTO_FVEC + (3 - 2)*UTO_DIV : 
		{
			const fvec<flt64_type,3>& v = *static_cast<const fvec<flt64_type,3>*>(value_ptr);
			if (dimension_independent) {

				fvec<flt32_type,3> vi = v; glUniform1fv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, (flt32_type)v[0], (flt32_type)v[1]); break;
				case 3 : glUniform3f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2]); break;
				case 4 : glUniform4f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2], (flt32_type)v[3]); break;

				default: { fvec<flt32_type,3> vi = v; glUniform1fv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT8+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<int8_type,4>& v = *static_cast<const fvec<int8_type,4>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT16+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<int16_type,4>& v = *static_cast<const fvec<int16_type,4>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_INT32+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<int32_type,4>& v = *static_cast<const fvec<int32_type,4>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, v[0], v[1]); break;
				case 3 : glUniform3i(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4i(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1iv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_UINT8+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<uint8_type,4>& v = *static_cast<const fvec<uint8_type,4>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT16+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<uint16_type,4>& v = *static_cast<const fvec<uint16_type,4>*>(value_ptr);
			if (dimension_independent) {

				fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: { fvec<int32_type,4> vi = v; glUniform1iv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_UINT32+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<uint32_type,4>& v = *static_cast<const fvec<uint32_type,4>*>(value_ptr);
			if (dimension_independent) {

				glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0]));
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2i(loc, (int32_type)v[0], (int32_type)v[1]); break;
				case 3 : glUniform3i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2]); break;
				case 4 : glUniform4i(loc, (int32_type)v[0], (int32_type)v[1], (int32_type)v[2], (int32_type)v[3]); break;

				default: glUniform1iv(loc, v.size(), reinterpret_cast<const int32_type*>(&v[0])); break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<flt32_type,4>& v = *static_cast<const fvec<flt32_type,4>*>(value_ptr);
			if (dimension_independent) {

				glUniform1fv(loc, v.size(), &v[0]);

			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, v[0], v[1]); break;
				case 3 : glUniform3f(loc, v[0], v[1], v[2]); break;
				case 4 : glUniform4f(loc, v[0], v[1], v[2], v[3]); break;

				default: glUniform1fv(loc, v.size(), &v[0]); break;

				}
			}
			break;
		}

	case TI_FLT64+UTO_FVEC + (4 - 2)*UTO_DIV : 
		{
			const fvec<flt64_type,4>& v = *static_cast<const fvec<flt64_type,4>*>(value_ptr);
			if (dimension_independent) {

				fvec<flt32_type,4> vi = v; glUniform1fv(loc, vi.size(), &vi[0]);
	
			}
			else {
				switch (v.size()) {
				case 2 : glUniform2f(loc, (flt32_type)v[0], (flt32_type)v[1]); break;
				case 3 : glUniform3f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2]); break;
				case 4 : glUniform4f(loc, (flt32_type)v[0], (flt32_type)v[1], (flt32_type)v[2], (flt32_type)v[3]); break;

				default: { fvec<flt32_type,4> vi = v; glUniform1fv(loc, vi.size(), &vi[0]); } break;
	
				}
			}
			break;
		}

	case TI_FLT32+UTO_FMAT + (2 - 2)*UTO_DIV:
		{
			const fmat<flt32_type,2,2>& m = *static_cast<const fmat<flt32_type,2,2>*>(value_ptr);
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}
	case TI_FLT64+UTO_FMAT + (2 - 2)*UTO_DIV:
		{
			const fmat<flt64_type,2,2>& md = *static_cast<const fmat<flt32_type,2,2>*>(value_ptr);
			fmat<flt32_type,2,2> m = md;
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}

	case TI_FLT32+UTO_FMAT + (3 - 2)*UTO_DIV:
		{
			const fmat<flt32_type,3,3>& m = *static_cast<const fmat<flt32_type,3,3>*>(value_ptr);
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}
	case TI_FLT64+UTO_FMAT + (3 - 2)*UTO_DIV:
		{
			const fmat<flt64_type,3,3>& md = *static_cast<const fmat<flt32_type,3,3>*>(value_ptr);
			fmat<flt32_type,3,3> m = md;
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}

	case TI_FLT32+UTO_FMAT + (4 - 2)*UTO_DIV:
		{
			const fmat<flt32_type,4,4>& m = *static_cast<const fmat<flt32_type,4,4>*>(value_ptr);
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}
	case TI_FLT64+UTO_FMAT + (4 - 2)*UTO_DIV:
		{
			const fmat<flt64_type,4,4>& md = *static_cast<const fmat<flt32_type,4,4>*>(value_ptr);
			fmat<flt32_type,4,4> m = md;
			switch (m.size()) {
			case  4 : glUniformMatrix2fv(loc, 1, 0, &m(0,0)); break;
			case  9 : glUniformMatrix3fv(loc, 1, 0, &m(0,0)); break;
			case 16 : glUniformMatrix4fv(loc, 1, 0, &m(0,0)); break;
			}
			break;
		}

